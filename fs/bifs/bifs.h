#ifndef BIFS_H_
#define BIFS_H_

#include <string>
#include <map>

#include "kernel/fs.h"

using namespace kernel;

namespace bifs {
    class BuiltInFilesystem : public Filesystem {
        public:
            using Filesystem::Filesystem;

            void add_file(path_t local_path, std::shared_ptr<std::vector<char>> data);

        protected:
            std::shared_ptr<File> _open(const path_t mount_point, FileMode mode);

        private:
            std::map<path_t, std::shared_ptr<std::vector<char>>> _file_data;
    };

    class BuiltInRegularFile : public RegularFile {
        public:
            BuiltInRegularFile(std::shared_ptr<Filesystem> filesystem, const path_t path, FileMode mode, std::shared_ptr<std::vector<char>> data);

            std::vector<char> read(size_t count);
            void write(std::vector<char> data);

        private:
            std::shared_ptr<std::vector<char>> _data;
    };
}

#endif