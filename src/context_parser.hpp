#pragma once

#include <cstddef>
#include <type_traits>
#include <vector>
#include <string_view>
#include <string>
#include <concepts>
#include <variant>

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
            {"--in", {"-i"}, "The path to the test directory defined in '$__TEMPENV_TESTS_DIR'. Defailts to /tmp/tempenv"},
            {"--with", {"-w"}, "Copies the listed files and directories into the newly created test environment or directory after exiting"},
            {"--removetest", {"-rt"}, "Removes the test located in the directory given"},
            {"--plain", {"--make-plain", "-p", "-mp"}, "Specifies that a testing environment should not have a '.tempenv' file."},
            {"--remove-when-exit", {"-r", "-rwe"}, "Specifies that a directory should be removed upon exiting with '--exit'"},
            {"--exit", {"-e"},
                "Exits the test directory and returns to the previous location before the test was created."
                "Previous directory stored in '$__TEMPENV_BEFORE_TEST_DIR' environment variable"}
        };
    }

    class context_parser { // Interprets the current environment (arguments, environment variables, .tempenv dotfile)
        public:

        context_parser() = default;
        context_parser(int argc, const char** argv);

        private:
        std::vector<std::string> args_list;

        std::string test_name {}; // Name of directory test is stored in
        std::string test_path {}; // Path to the directory in which the test directory will be stored (defaults to $home/tests)
        std::string current_directory {}; // Current directory at runtime

        bool is_in_test_directory {};
        bool remove_when_done {};
    };
}

