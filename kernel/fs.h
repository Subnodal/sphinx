#ifndef KERNEL_FS_H_
#define KERNEL_FS_H_

#include <string>
#include <memory>
#include <vector>

#include "stream.h"

namespace kernel {
    typedef std::string path_t;
    typedef size_t fd_t;

    enum FileMode {
        READ_ONLY   = 0x01,
        WRITE_ONLY  = 0x02,
        READ_WRITE  = 0x04,
        APPEND      = 0x08,
        CREATE      = 0x10,
        TRUNCATE    = 0x20
    };

    class FilesystemTable;
    class File;

    class Filesystem : public std::enable_shared_from_this<Filesystem> {
        public:
            Filesystem(FilesystemTable* table, const path_t mount_point);

            const path_t get_mount_point();

            virtual std::shared_ptr<File> open(const path_t mount_point, FileMode mode) = 0;

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

        private:
            friend class Filesystem;

            const fd_t _file_descriptor;
            const std::weak_ptr<Filesystem> _filesystem;
            const path_t _path;
            const FileMode _mode;

            File(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode);
    };

    class StreamedFile : public File, public Stream {};

    class RegularFile : public StreamedFile {};
}

#endif