#include "fs.h"

using namespace kernel;

Filesystem::Filesystem(FilesystemTable* table, const path_t mount_point)
: _table(table)
, _mount_point(mount_point) {}

const path_t Filesystem::get_mount_point() {
    return _mount_point;
}

void FilesystemTable::add(std::shared_ptr<Filesystem> filesystem) {
    _filesystems.push_back(filesystem);
}

std::shared_ptr<Filesystem> FilesystemTable::get_mounted_filesystem(const path_t path) {
    for (std::shared_ptr<Filesystem> filesystem : _filesystems) {
        if (filesystem->get_mount_point().compare(0, path.length(), path) == 0) {
            return filesystem;
        }
    }

    return nullptr;
}

std::shared_ptr<File> FilesystemTable::get_file_by_file_descriptor(fd_t file_descriptor) {
    for (std::shared_ptr<File> file : _files) {
        if (file->get_file_descriptor() == file_descriptor) {
            return file;
        }
    }

    return nullptr;
}

File::File(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode)
: _file_descriptor(filesystem->_table->_next_file_descriptor++)
, _filesystem(filesystem)
, _path(path)
, _mode(mode) {}

fd_t File::get_file_descriptor() {
    return _file_descriptor;
}