#ifndef KERNEL_FS_H_
#define KERNEL_FS_H_

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

#include "stream.h"

namespace kernel {
    typedef std::string path_t;
    typedef size_t fd_t;

    enum FileMode {
        READ        = 0x01,
        WRITE       = 0x02,
        READ_WRITE  = 0x03, // Read and write
        APPEND      = 0x04,
        CREATE      = 0x08,
        TRUNCATE    = 0x10
    };

    class FilesystemTable;
    class File;

    class FileError : public std::runtime_error {
        public:
            FileError(const std::string& what);
    };

    class Filesystem : public std::enable_shared_from_this<Filesystem> {
        public:
            Filesystem(const path_t mount_point);
            virtual ~Filesystem() {}

            FilesystemTable* get_table();
            const path_t get_mount_point();
            bool is_subpath(const path_t path);

            std::shared_ptr<File> open(const path_t path, FileMode mode);

        protected:
            virtual std::shared_ptr<File> _open(const path_t path, FileMode mode) = 0;

        private:
            friend class FilesystemTable;
            friend class File;

            FilesystemTable* _table = nullptr;
            const path_t _mount_point;
    };

    class FilesystemTable {
        public:
            void add(std::shared_ptr<Filesystem> filesystem);

            std::shared_ptr<Filesystem> get_mounted_filesystem(const path_t path);
            std::shared_ptr<File> get_file_by_file_descriptor(fd_t file_descriptor);

            std::shared_ptr<File> open(const path_t path, FileMode mode);

        private:
            friend class Filesystem;
            friend class File;

            std::vector<std::shared_ptr<Filesystem>> _filesystems;
            std::vector<std::shared_ptr<File>> _files;
            fd_t _next_file_descriptor = 0;
    };

    class File : public Stream, public std::enable_shared_from_this<File> {
        public:
            File(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode);

            fd_t get_file_descriptor();
            const FileMode get_mode();
            size_t get_offset();
            void set_offset(size_t offset);
            size_t increment_offset(size_t count, bool writing = false);
            size_t get_size();

        protected:
            void _set_size(size_t size);

        private:
            friend class Filesystem;

            fd_t _file_descriptor;
            const std::weak_ptr<Filesystem> _filesystem;
            const path_t _path;
            const FileMode _mode;
            size_t _offset = 0;
            size_t _size = 0;
    };

    class SeekableFile : public File {
        public:
            using File::File;
    };

    class RegularFile : public SeekableFile {
        public:
            using SeekableFile::SeekableFile;
    };
}

#endif