#include "fs.h"

using namespace kernel;

Filesystem::Filesystem(FilesystemTable* table, const path_t mount_point)
: _table(table)
, _mount_point(mount_point) {}

FilesystemTable* Filesystem::get_table() {
    return _table;
}

const path_t Filesystem::get_mount_point() {
    return _mount_point;
}

bool Filesystem::is_subpath(const path_t path) {
    return path == _mount_point || (path + "/").compare(0, _mount_point.length(), _mount_point) == 0;
}

void FilesystemTable::add(std::shared_ptr<Filesystem> filesystem) {
    _filesystems.push_back(filesystem);
}

std::shared_ptr<Filesystem> FilesystemTable::get_mounted_filesystem(const path_t path) {
    for (std::shared_ptr<Filesystem> filesystem : _filesystems) {
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

File::File(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode)
: _file_descriptor(filesystem->_table->_next_file_descriptor++)
, _filesystem(filesystem)
, _path(path)
, _mode(mode) {
    filesystem->_table->_files.push_back(shared_from_this());
}

fd_t File::get_file_descriptor() {
    return _file_descriptor;
}

const FileMode File::get_mode() {
    return _mode;
}

StreamableFile::StreamableFile(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode)
: File(filesystem, path, mode)
, Stream() {}

SeekableFile::SeekableFile(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode)
: StreamableFile(filesystem, path, mode) {}

size_t SeekableFile::get_offset() {
    return _offset;
}

void SeekableFile::set_offset(size_t offset) {
    if (_offset > _size || ((get_mode() & FileMode::WRITE) && _offset == _size)) {
        throw FileError("attempt to seek beyond end of file");
    }

    _offset = offset;
}

size_t SeekableFile::get_size() {
    return _size;
}

void SeekableFile::_set_size(size_t size) {
    _size = size;
}