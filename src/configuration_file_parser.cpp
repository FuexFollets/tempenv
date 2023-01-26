#include <string>
#include <filesystem>
#include <string_view>
#include <toml++/toml.h>

#include "./headers/configuration_file_parser.hpp"

namespace tempenv {
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
}
