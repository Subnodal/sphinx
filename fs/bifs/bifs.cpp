#include "bifs.h"

using namespace kernel;
using namespace bifs;

std::shared_ptr<File> BuiltInFilesystem::_open(const path_t path, FileMode mode) {
    if (!is_subpath(path)) {
        return nullptr;
    }

    path_t subpath = path.substr(get_mount_point().length());

    if (!_file_data.count(subpath)) {
        return nullptr;
    }


    return std::make_shared<BuiltInRegularFile>(shared_from_this(), path, mode, _file_data[subpath]);
}

void BuiltInFilesystem::add_file(path_t local_path, std::shared_ptr<std::vector<char>> data) {
    _file_data[local_path] = data;
}

bifs::BuiltInRegularFile::BuiltInRegularFile(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode, std::shared_ptr<std::vector<char>> data)
: RegularFile(filesystem, path, mode)
, _data(data) {
    _set_size(data->size());
}

std::vector<char> BuiltInRegularFile::read(size_t count) {
    auto start = _data->begin() + get_offset();
    size_t actual_count = increment_offset(count);

    return std::vector<char>(
        start,
        start + actual_count + 1
    );
}

void BuiltInRegularFile::write(std::vector<char> data) {
    throw FileError("read-only file");
}