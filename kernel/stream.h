#ifndef KERNEL_STREAM_H_
#define KERNEL_STREAM_H_

#include <string>
#include <vector>
#include <memory>

namespace kernel {
    class Stream {
        public:
            virtual std::vector<char> read(size_t count) = 0;
            virtual void write(std::vector<char> data) = 0;

            void print(const char c);
            void print(const std::string data);

            template<class... Args> void print(const std::string data, Args... args) {
                print(data);
                print(' ');
                print(args...);
            }

            void println(const char c);
            void println(const std::string data);

            template<class... Args> void println(const std::string data, Args... args) {
                print(data, args...);
                print('\n');
            }
    };
}

#endif