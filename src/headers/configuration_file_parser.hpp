#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <exception>

namespace tempenv {
    struct configuration_file {
        std::filesystem::path tests_location;
        bool tests_location_is_specified {};

        std::vector<std::string> copied_with;
        std::vector<std::vector<std::string>> executed_in_test_directory;

        configuration_file() = default;

        explicit configuration_file(const std::filesystem::path& path_to_configuration_file, const std::vector<std::string>& chosen_preset_names);


        struct presets_do_not_exist : std::exception {
            using std::exception::what;

            explicit presets_do_not_exist(const std::vector<std::string>&);

            std::vector<std::string> nonexistent_presets;

            const char* what();
        };
    };
}

