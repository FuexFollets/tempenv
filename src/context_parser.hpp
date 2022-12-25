#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>
#include <string_view>
#include <string>
#include <concepts>
#include <filesystem>
#include <cstring>
#include <algorithm>
#include <functional>
#include <exception>

namespace tempenv { namespace constraints {
        template <typename T, typename type_constructed>
        concept can_construct = std::is_constructible<type_constructed, T>::value;

        template <typename T>
        concept string_view_constructible = std::is_constructible_v<std::string_view, T>;
    }

    namespace cli_options { // All cli arguments

        struct invalid_option : std::exception {
            std::string what_string;

            explicit invalid_option(const constraints::can_construct<std::string> auto& message) : what_string {message} {};

            using std::exception::what;

            const char* what() {
                char* c_what_string {new char[what_string.size()]};

                return std::strcpy(c_what_string, what_string.c_str());
            }
        };

        struct option {
            std::vector<std::string_view> name_ailases;
            std::string_view description;
        };

        enum OptionType { // Index for option in options list for `name` or `with`
            Name = 1, With = 3
        };

        const std::vector<option> options_list { // A listing of all options as cli_options::option types
            {{"--help", "-h"}, "Lists all available options and descriptions or description(s) for the listed options"},
            {{"--name", "-n"}, "Indicates the name of the name of the test to create (and the directory which the test is stored in)"},
            {{"--in", "-i"}, "The path to the test directory. Defaultly defined in '$__TEMPENV_TESTS_DIR'. Defailts to /tmp/tempenv"},
            {{"--with", "-w"}, "Copies the listed files and directories into the newly created test environment or directory after exiting"},
            {{"--plain", "--make-plain", "-p", "-mp"}, "Specifies that a testing environment should not have a '.tempenv' file."},
            {{"--exit", "-e"},
                "Prints the previous location before the test was created. "
                "Previous directory stored in '$__TEMPENV_BEFORE_TEST_DIR' environment variable"},
            {{"--last-test", "-lt", "-l"}, "Prints the directory of the last test. Directory path stored in '$__TEMPENV_BEFORE_TEST_DIR'"}
        };

        const auto& options_with {options_list.at(OptionType::With).name_ailases};
        const auto& options_name {options_list.at(OptionType::Name).name_ailases};

        inline bool is_option_at_index(std::size_t index, const constraints::string_view_constructible auto& tested_option_name) {
            return std::count(
                    options_list.at(index).name_ailases.begin(),
                    options_list.at(index).name_ailases.end(),
                    std::string_view {tested_option_name}
                ) > 0;
        }


        inline bool is_copy_with_option(const constraints::string_view_constructible auto& tested_option_name) {
            return is_option_at_index(OptionType::With, tested_option_name);
        }

        inline bool is_name_option(const constraints::string_view_constructible auto& tested_option_name) {
            return is_option_at_index(OptionType::Name, tested_option_name);
        }

        bool is_option(const constraints::string_view_constructible auto& tested_option_name) {
            const std::string_view string_view_tested_option_name {tested_option_name};
            for (const option& opt: options_list) {
                for (const std::string_view& name_alias: opt.name_ailases) {
                    if (name_alias == string_view_tested_option_name) { return true; }
                }
            }
            return false;
        }
    } // End of namespace cli_options

    class context_parser { // Interprets the current environment (arguments, environment variables, .tempenv dotfile)
        public:

        context_parser() = default;
        context_parser(int argc, const char** argv);

        private:
        std::vector<std::string_view> args_list;


        struct {
            std::filesystem::path test_location {}; // Path to the directory in which the test directory will be stored (defaults to viable testing directory)
            std::vector<std::filesystem::path> copied_with;
            std::string_view test_name {};
            std::filesystem::path test_name_path {}; // Name of directory test is stored in
            bool remove_when_done {}; 
            bool is_plain {};
        } parsed_args;

        struct {
            std::filesystem::path last_test; // Directory to the most recent test directory
            std::filesystem::path current_directory {}; // Current directory when first executed
            bool is_in_test_directory {};
        } parsed_environment;
    };


    context_parser::context_parser(int argc, const char** argv) {
        // Initialize args_list
        const char** first_arg {argv};
        const char** last_arg {argv};

        std::advance(first_arg, 1);
        std::advance(last_arg, argc);

        std::copy(first_arg, last_arg, std::back_inserter(args_list));

        // Interpret arg list
        bool is_currently_name {}; bool already_listed_name {};
        bool is_currently_listing_copied_with {}; bool already_listed_copied_with {};

        for (const auto& argument: args_list) {
            if (is_currently_name) {
                parsed_args.test_name = argument;
                already_listed_name = true;
                is_currently_name = false;
                continue;
            }

            if (is_currently_listing_copied_with) {
                if (cli_options::is_option(argument)) {
                    already_listed_copied_with = true;
                    is_currently_listing_copied_with = false;
                    continue;
                }

                parsed_args.copied_with.emplace_back(argument);
                continue;
            }

            if (cli_options::is_copy_with_option(argument)) {
                is_currently_listing_copied_with = true;
                continue;
            }

            if (cli_options::is_name_option(argument)) {
                is_currently_name = true;
                continue;
            }
        }

        // Initialize paths and names
        parsed_environment.current_directory = std::filesystem::current_path();

        auto specified_path {std::filesystem::path(std::getenv("__TEMPENV_TESTS_DIR"))};

        parsed_args.test_location = std::filesystem::is_directory(specified_path) ?
            std::filesystem::path(specified_path) :
            std::filesystem::path(std::filesystem::temp_directory_path().string() + "tempenv");
    }
}

