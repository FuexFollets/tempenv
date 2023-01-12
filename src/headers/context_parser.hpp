#pragma once

#include <filesystem>
#include <string>
#include <nlohmann/json.hpp>

namespace tempenv {
    std::filesystem::path home_directory_path();

    class environment_context {
        // Directory to the last time in a test. Reads from `$__TEMPENV_LAST_TEST_PATH`
        std::filesystem::path _last_test_path {};
        // String path to the last working directory. Reads from `$__TEMPENV_BEFORE_TEST_PATH`
        std::filesystem::path _last_working_directory {};
        bool _is_in_testing_directory {}; // Determines if the current directory has a `.tempenv` file
        // Directory of the configuration file.
        std::filesystem::path _config_directory_path {};
        nlohmann::json _config_file_contents {};
        bool _config_file_exists {};
        // Directory where the testing directory will be created.
        std::filesystem::path _temp_directory_path {};

        public:

        environment_context();

        // Getters
        [[nodiscard]] std::filesystem::path last_test_path() const;
        [[nodiscard]] std::filesystem::path last_working_directory() const;
        [[nodiscard]] std::filesystem::path config_directory_path() const;
        [[nodiscard]] std::filesystem::path temp_directory_path() const;
        [[nodiscard]] std::string config_file_contents() const;
        [[nodiscard]] bool config_file_exists() const;
        [[nodiscard]] bool is_in_testing_directory() const; // Works
    };
} // End of namespace tempenv
