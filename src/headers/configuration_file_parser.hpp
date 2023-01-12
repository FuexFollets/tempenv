#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <exception>
#include <nlohmann/json.hpp>

namespace tempenv {
    class configuration_file {
        std::filesystem::path _tests_location;
        bool _is_valid_tests_location_provided {};

        std::vector<std::string> _copy_with;
        std::vector<std::string> _execute_in_test_directory;

        std::vector<std::string> _invalid_presets;

        public:

        configuration_file() = default;

        configuration_file(const nlohmann::json& configuration_json_file, const std::vector<std::string>& chosen_preset_names);
    };
}

