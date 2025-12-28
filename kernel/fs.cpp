#include "fs.h"

#include <iostream>

using namespace kernel;

FileError::FileError(const std::string& what = "")
: std::runtime_error(what) {}

Filesystem::Filesystem(const path_t mount_point)
: _mount_point(mount_point) {}

FilesystemTable* Filesystem::get_table() {
    return _table;
}

const path_t Filesystem::get_mount_point() {
    return _mount_point;
}

bool Filesystem::is_subpath(const path_t path) {
    return path == _mount_point || (path + "/").compare(0, _mount_point.length(), _mount_point) == 0;
}

std::shared_ptr<File> Filesystem::open(const path_t path, FileMode mode) {
    std::shared_ptr<File> file = _open(path, mode);

    if (!file) {
        return nullptr;
    }

    file->_file_descriptor = get_table()->_next_file_descriptor++;

    _table->_files.push_back(file);

    return file;
}

void FilesystemTable::add(std::shared_ptr<Filesystem> filesystem) {
    filesystem->_table = this;

    _filesystems.push_back(filesystem);
}

std::shared_ptr<Filesystem> FilesystemTable::get_mounted_filesystem(const path_t path) {
    for (std::shared_ptr<Filesystem> filesystem : _filesystems) {
        std::cout << filesystem->get_mount_point() << " " << path << std::endl;
        if (filesystem->is_subpath(path)) {
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

std::shared_ptr<File> FilesystemTable::open(const path_t path, FileMode mode) {
    std::shared_ptr<Filesystem> filesystem = get_mounted_filesystem(path);

    if (!filesystem) {
        return nullptr;
    }

    return filesystem->open(path, mode);
}

File::File(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode)
: _filesystem(filesystem)
, _path(path)
, _mode(mode) {}

fd_t File::get_file_descriptor() {
    return _file_descriptor;
}

const FileMode File::get_mode() {
    return _mode;
}

size_t File::get_offset() {
    return _offset;
}

void File::set_offset(size_t offset) {
    if (offset > _size || (!(get_mode() & FileMode::WRITE) && offset == _size)) {
        throw FileError("attempt to seek beyond end of file");
    }

    _offset = offset;
}

size_t File::increment_offset(size_t count, bool writing) {
    size_t original_offset = get_offset();
    size_t actual_offset = original_offset + count;

    if (!writing && actual_offset >= _size) {
        actual_offset = _size - 1;
    }

    set_offset(actual_offset);

    return actual_offset - original_offset;
}

size_t File::get_size() {
    return _size;
}

void File::_set_size(size_t size) {
    _size = size;
}