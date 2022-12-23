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

namespace tempenv { namespace constraints {
        template <typename T, typename type_constructed>
        concept can_construct = std::is_constructible<type_constructed, T>::value;
    }

    namespace cli_options { // All cli arguments
        struct option {
            std::string_view name;
            std::vector<std::string_view> aliases;
            std::string_view description;
        };

        const std::vector<option> options_list {
            {"--help", {"-h"}, "Lists all available options and descriptions or description(s) for the listed options"},
            {"--name", {"-n"}, "Indicates the name of the name of the test (and the directory which the test is stored in)"},
            {"--in", {"-i"}, "The path to the test directory. Defaultly defined in '$__TEMPENV_TESTS_DIR'. Defailts to /tmp/tempenv"},
            {"--with", {"-w"}, "Copies the listed files and directories into the newly created test environment or directory after exiting"},
            {"--plain", {"--make-plain", "-p", "-mp"}, "Specifies that a testing environment should not have a '.tempenv' file."},
            {"--exit", {"-e"},
                "Prints the previous location before the test was created. "
                "Previous directory stored in '$__TEMPENV_BEFORE_TEST_DIR' environment variable"},
            {"--last-test", {"-lt", "-l"}, "Prints the directory of the last test. Directory path stored in '$__TEMPENV_BEFORE_TEST_DIR'"}
        };

        bool is_option(const auto option_name) requires std::is_constructible_v<std::string_view, decltype(option_name)> {
            return std::any_of(
                options_list.begin(), options_list.end(),
                [&] (const auto& option_in_list) { return option_in_list == option_name; });
        }
    }

    class context_parser { // Interprets the current environment (arguments, environment variables, .tempenv dotfile)
        public:

        context_parser() = default;
        context_parser(int argc, const char** argv);

        private:
        std::vector<std::string_view> args_list;


        struct {
            std::filesystem::path test_location {}; // Path to the directory in which the test directory will be stored (defaults to viable testing directory)
            std::vector<std::filesystem::path> copied_with;
            std::filesystem::path test_name {}; // Name of directory test is stored in
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


        // Initialize paths and names
        parsed_environment.current_directory = std::filesystem::current_path();


        const char* tests_dir_environment_variable = std::getenv("__TEMPENV_TESTS_DIR");

        auto specified_path {std::filesystem::path(tests_dir_environment_variable)};

        test_location = std::filesystem::is_directory(specified_path) ?
            std::filesystem::path(specified_path) :
            std::filesystem::path(std::filesystem::temp_directory_path().string() + "tempenv");
    }
}

