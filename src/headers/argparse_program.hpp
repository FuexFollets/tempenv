#ifndef TEMPENV_ARGPARSE_PROGRAM_HPP
#define TEMPENV_ARGPARSE_PROGRAM_HPP
#pragma once

#include <optional>
#include <string>
#include <filesystem>
#include <exception>

#include <argparse/argparse.hpp>

#include "context_parser.hpp"

namespace tempenv {
    class tempenv_argument_parser {
        private:

        std::string _test_name {};
        std::optional<std::filesystem::path> _test_directory {};
        std::optional<std::filesystem::path> _configuration_file_location {};

        argparse::ArgumentParser program;

        void initialize_program();

        public:

        [[nodiscard]] std::string test_name() const;
        [[nodiscard]] std::optional<std::filesystem::path> test_directory() const;
        [[nodiscard]] std::optional<std::filesystem::path> configuration_file_location() const;

        tempenv_argument_parser() = default;
        tempenv_argument_parser(int argc, const char** argv);
    };
}

#endif
