#pragma once

#include <filesystem>
#include <stack>
#include <string>

namespace tempenv {
    struct environment_context {
        struct {
            std::filesystem::path last_test_path {}; // Directory to the last time in a test. Reads from `$__TEMPENV_LAST_TEST_PATH`
            std::filesystem::path last_working_directory {}; // String path to the last working directory. Reads from `$__TEMPENV_BEFORE_TEST_PATH`
        } environment_variables;

        struct {
            bool is_in_testing_directory {}; // Determines if the current directory has a `.tempenv` file

            // Read from `~/.config/tempenv`
            std::filesystem::path config_directory_path {}; // Directory of the configuration file.
            std::string config_file_contents {}; // Contents of the configuration file
            bool config_file_exists {};
            std::filesystem::path temp_directory_path {}; // Directory where the testing directory will be created.
        } environment_files;

        environment_context();
    };
} // End of namespace tempenv
