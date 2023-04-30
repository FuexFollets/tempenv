#ifndef TEMPENV_ARGPARSE_PROGRAM_HPP
#define TEMPENV_ARGPARSE_PROGRAM_HPP
#pragma once

#include <exception>
#include <filesystem>
#include <optional>
#include <string>

#include <argparse/argparse.hpp>

namespace tempenv {
    class tempenv_argument_parser {
        private:

        std::string _test_name {};
        std::optional<std::filesystem::path> _test_directory {};
        std::optional<std::filesystem::path> _configuration_file_location {};
        std::optional<std::vector<std::string>> _selected_preset_names {};

        argparse::ArgumentParser program;

        void initialize_program();

        public:

        [[nodiscard]] std::string test_name() const;
        [[nodiscard]] std::optional<std::filesystem::path> test_directory() const;
        [[nodiscard]] std::optional<std::filesystem::path> configuration_file_location() const;
        [[nodiscard]] std::optional<std::vector<std::string>> selected_preset_names() const;

        tempenv_argument_parser() = default;
        tempenv_argument_parser(int argc, const char** argv);
    };
} // namespace tempenv

#endif
