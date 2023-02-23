#ifndef TEMPENV_ARGPARSE_PROGRAM_HPP

#include <optional>
#include <string>
#include <filesystem>
#include <exception>

#include <argparse/argparse.hpp>

namespace tempenv {
    class tempenv_argument_parser {
        private:

        std::string _test_name;
        std::optional<std::filesystem::path> _test_directory;

        argparse::ArgumentParser program;

        void initialize_program();

        public:

        [[nodiscard]] std::string test_name() const;
        [[nodiscard]] std::optional<std::filesystem::path> test_directory() const;

        tempenv_argument_parser() = default;
        tempenv_argument_parser(int argc, const char** argv);
    };
}

#endif
