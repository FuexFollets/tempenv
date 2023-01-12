#include <exception>
#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <algorithm>

#include "./headers/configuration_file_parser.hpp"

namespace tempenv {
    configuration_file::configuration_file(const nlohmann::json& configuration_json_file, const std::vector<std::string>& chosen_preset_names) :
        _is_valid_tests_location_provided {configuration_json_file.contains("tests-location")} {

        if (_is_valid_tests_location_provided) {
            _tests_location = configuration_json_file
                .at("tests-location")
                .get<std::filesystem::path>();
        }

        if (!configuration_json_file.contains("presets")) { return; } // Configuration file does not contain presets section

        const auto& configuration_presets {configuration_json_file.at("presets")};
        const auto configuration_preset_items {configuration_presets.items()};
        std::vector<std::string> valid_presets;

        for (const std::string& chosen_preset: chosen_preset_names) { // Separate valid and invalid chosen presets
            if (std::any_of(configuration_preset_items.begin(), configuration_preset_items.end(),
                    [&] (const auto& preset_item) { return preset_item.key() == chosen_preset; })) {
                valid_presets.push_back(chosen_preset);
            } else { _invalid_presets.push_back(chosen_preset); }
        }

        for (const std::string& valid_preset: valid_presets) {
            const auto configured_preset {configuration_presets.at(valid_preset)};

            const auto paths_to_copy_with {configured_preset.at("copy-with").get<std::vector<std::filesystem::path>>()};
            const auto executed {configured_preset.at("execute-in-test-directory").get<std::vector<std::vector<std::string>>>()};

            _copy_with.insert(_copy_with.end(), paths_to_copy_with.begin(), paths_to_copy_with.end());
            _execute_in_test_directory.insert(_execute_in_test_directory.begin(), executed.begin(), executed.end());
        }
    }


    bool configuration_file::is_valid_tests_location_provided() const {
        return _is_valid_tests_location_provided;
    }


    std::filesystem::path configuration_file::tests_location() const {
        return _tests_location;
    }


    std::vector<std::filesystem::path> configuration_file::copy_with() const {
        return _copy_with;
    }


    std::vector<std::vector<std::string>> configuration_file::execute_in_test_directory() const {
        return _execute_in_test_directory;
    }


    std::vector<std::string> configuration_file::invalid_presets() const {
        return _invalid_presets;
    }
}
