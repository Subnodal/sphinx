#include "bifs.h"

using namespace kernel;
using namespace bifs;

std::shared_ptr<File> BuiltInFilesystem::open(const path_t path, FileMode mode) {
    if (!is_subpath(path)) {
        return nullptr;
    }

    path_t subpath = path.substr(get_mount_point().length());

    if (!_file_data.count(subpath)) {
        return nullptr;
    }
}

void BuiltInFilesystem::add_file(path_t local_path, std::shared_ptr<std::vector<char>> data) {
    _file_data[local_path] = data;
}

BuiltInRegularFile::BuiltInRegularFile(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode, std::weak_ptr<std::vector<char>> data)
: RegularFile(filesystem, path, mode)
, _data(data) {}