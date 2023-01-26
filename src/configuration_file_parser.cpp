#include <string>
#include <filesystem>
#include <string_view>
#include <toml++/toml.h>

#include "./headers/configuration_file_parser.hpp"

namespace tempenv {
    configuration_file::preset::preset(std::string&& preset_name, const toml::table& preset_table) :
        _name {preset_name},
        _copy_with {preset_table.at("copy_with")
            .value<std::vector<std::filesystem::path>>()
            .value_or(std::vector<std::filesystem::path> {})
        },
        _execute_in_test_directory {preset_table.at("execute_in_test_directory")
            .value<std::vector<std::vector<std::string>>>()
            .value_or(std::vector<std::vector<std::string>> {})
        }
        {}

    std::string configuration_file::preset::name() const {
        return _name;
    }

    std::vector<std::filesystem::path> configuration_file::preset::copy_with() const {
        return _copy_with;
    }

    std::vector<std::vector<std::string>> configuration_file::preset::execute_in_test_directory() const {
        return _execute_in_test_directory;
    }

    configuration_file::configuration_file(const toml::table& parsed_config_file) :
        _tests_location {parsed_config_file.at("tests_location").as_string() -> get()},
        _is_valid_tests_location_provided {std::filesystem::exists(_tests_location)} {

        _forall_presets = preset (
            std::string {},
            *parsed_config_file.at("forall_presets").as_table()
        );

        for (auto&&[key, value]: parsed_config_file) {
            const std::string_view key_name {key.str()};

            if (key_name.starts_with("preset.")) {
                _available_presets.push_back(preset (
                    std::string {}, *value.as_table()
                ));
            }
        }
    }

    bool configuration_file::is_valid_tests_location_provided() const {
        return _is_valid_tests_location_provided;
    }

    std::filesystem::path configuration_file::tests_location() const {
        return _tests_location;
    }

    std::vector<configuration_file::preset> configuration_file::available_presets() const {
        return _available_presets;
    }

    std::vector<std::filesystem::path>
        configuration_file::copy_with(const std::vector<std::string>& presets_to_copy) const {
        std::vector<std::filesystem::path> paths_to_copy_with {};

        for (const preset& available_preset: _available_presets) {
            for (const std::string& preset_to_copy: presets_to_copy) {
                if (preset_to_copy == available_preset.name()) {
                    paths_to_copy_with.insert(
                            paths_to_copy_with.end(),
                            available_preset.copy_with().cbegin(),
                            available_preset.copy_with().cend()
                    );
                }
            }
        }

        return paths_to_copy_with;
    }
}
