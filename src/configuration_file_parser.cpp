#include <exception>
#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <algorithm>

#include "./headers/configuration_file_parser.hpp"

namespace tempenv {
    configuration_file::configuration_file(const std::filesystem::path& path_to_configuration_file, const std::vector<std::string>& chosen_preset_names) {
        nlohmann::json configuration_json_file {}; // Json type containing configuration

        std::ifstream {path_to_configuration_file} >> configuration_json_file; // Parsing the json file in the specified path
        configuration_json_file = configuration_json_file[0];

        tests_location_is_specified = configuration_json_file.contains("tests-location");

        if (tests_location_is_specified) {
            tests_location = configuration_json_file[0]
                .at("tests-location")
                .get<std::filesystem::path>();
        }

        if (!configuration_json_file.contains("presets")) { return; } // Configuration file does not contain presets section

        const auto& configuration_presets {configuration_json_file.at("presets")};
        const auto& configuration_preset_items {configuration_presets.items()};
        std::vector<std::string> valid_presets;

        for (const std::string& chosen_preset: chosen_preset_names) { // Separate valid and invalid chosen presets
            if (std::any_of(configuration_preset_items.begin(), configuration_preset_items.end(),
                    [&] (const auto& preset_item) { return preset_item.key() == chosen_preset; })) {
                valid_presets.push_back(chosen_preset);
            } else { invalid_presets.push_back(chosen_preset); }
        }

        for (const std::string& valid_preset : valid_presets) {
            const auto& configured_preset {configuration_presets.at(valid_preset)};

            copy_with = configured_preset.at("copy-with").get<std::vector<std::string>>();
            execute_in_test_directory = configured_preset.at("execute-in-test-directory").get<std::vector<std::string>>();
        }
    }
}
