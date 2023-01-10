#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <exception>

namespace tempenv {
    struct configuration_file {
        std::filesystem::path tests_location;
        bool tests_location_is_specified {};

        std::vector<std::string> copy_with;
        std::vector<std::string> execute_in_test_directory;

        std::vector<std::string> invalid_presets;

        configuration_file() = default;

        explicit configuration_file(const std::filesystem::path& path_to_configuration_file, const std::vector<std::string>& chosen_preset_names);
    };
}

