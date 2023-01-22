#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <exception>
#include <yaml.h>

namespace tempenv {
    class configuration_file {
        std::filesystem::path _tests_location;
        bool _is_valid_tests_location_provided {};

        std::vector<std::filesystem::path> _copy_with;
        std::vector<std::vector<std::string>> _execute_in_test_directory;

        std::vector<std::string> _invalid_presets;

        public:

        configuration_file() = default;

        [[nodiscard]] bool is_valid_tests_location_provided() const;
        [[nodiscard]] std::filesystem::path tests_location() const;
        [[nodiscard]] std::vector<std::filesystem::path> copy_with() const;
        [[nodiscard]] std::vector<std::vector<std::string>> execute_in_test_directory() const;
        [[nodiscard]] std::vector<std::string> invalid_presets() const;
    };
}

