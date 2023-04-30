#ifndef TEMPENV_DECISION_MAKER_HPP
#define TEMPENV_DECISION_MAKER_HPP
#pragma once

#include <filesystem>
#include <string>

#include <argparse/argparse.hpp>
#include <toml++/toml.h>

#include "argparse_program.hpp"
#include "configuration_file_parser.hpp"
#include "defaults.hpp"

namespace tempenv {
    class decision_maker {
        private:

        bool _default_test_location_chosen {};
        std::filesystem::path _tests_location {};
        std::string _test_name {};
        std::vector<std::filesystem::path> _copy_with {};
        std::vector<std::vector<std::string>> _execute_in_test_directory {};

        public:

        [[nodiscard]] bool default_test_location_chosen() const;
        [[nodiscard]] std::filesystem::path tests_location() const;
        [[nodiscard]] std::string test_name() const;
        [[nodiscard]] std::vector<std::filesystem::path> copy_with() const;
        [[nodiscard]] std::vector<std::vector<std::string>> execute_in_test_directory() const;

        explicit decision_maker(const tempenv_argument_parser& parsed_arguments);
    };
} // namespace tempenv

#endif
