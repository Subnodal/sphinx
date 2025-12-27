#ifndef BIFS_H_
#define BIFS_H_

#include <string>
#include <map>

#include "kernel/fs.h"

using namespace kernel;

namespace bifs {
    class BuiltInFilesystem : public Filesystem {
        public:
            std::shared_ptr<File> open(const path_t mount_point, FileMode mode);

            void add_file(path_t local_path, std::shared_ptr<std::vector<char>> data);

        private:
            std::map<path_t, std::shared_ptr<std::vector<char>>> _file_data;
    };

    class BuiltInRegularFile : public RegularFile {
        protected:
            BuiltInRegularFile(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode, std::weak_ptr<std::vector<char>> data);

        private:
            std::shared_ptr<std::vector<char>> _data;
    };
}

#endif