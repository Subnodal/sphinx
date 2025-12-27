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
            Filesystem(FilesystemTable* table, const path_t mount_point);

            FilesystemTable* get_table();
            const path_t get_mount_point();
            bool is_subpath(const path_t path);

            virtual std::shared_ptr<File> open(const path_t path, FileMode mode) = 0;

        private:
            friend class File;

            FilesystemTable* _table;
            const path_t _mount_point;
    };

    class FilesystemTable {
        public:
            void add(std::shared_ptr<Filesystem> filesystem);

            std::shared_ptr<Filesystem> get_mounted_filesystem(const path_t path);
            std::shared_ptr<File> get_file_by_file_descriptor(fd_t file_descriptor);

        private:
            friend class File;

            std::vector<std::shared_ptr<Filesystem>> _filesystems;
            std::vector<std::shared_ptr<File>> _files;
            fd_t _next_file_descriptor;
    };

    class File : std::enable_shared_from_this<File> {
        public:
            fd_t get_file_descriptor();
            const FileMode get_mode();

        protected:
            File(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode);

        private:
            friend class Filesystem;

            const fd_t _file_descriptor;
            const std::weak_ptr<Filesystem> _filesystem;
            const path_t _path;
            const FileMode _mode;
    };

    class StreamableFile : public File, public Stream {
        protected:
            StreamableFile(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode);
    };

    class SeekableFile : public StreamableFile {
        public:
            size_t get_offset();
            void set_offset(size_t offset);
            size_t get_size();

        protected:
            SeekableFile(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode);

            void _set_size(size_t size);

        private:
            size_t _offset = 0;
            size_t _size = 0;
    };

    class RegularFile : public SeekableFile {
        protected:
            using SeekableFile::SeekableFile;
    };
}

#endif