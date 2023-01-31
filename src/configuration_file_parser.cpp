#include <functional>
#include <optional>
#include <string>
#include <filesystem>
#include <string_view>
#include <toml++/toml.h>

#include "./headers/configuration_file_parser.hpp"

namespace tempenv {
    configuration_file::preset::preset(std::string&& preset_name, const toml::table& preset_table) :
        _name {preset_name} {
            for (const toml::node& path: *preset_table.at("copy_with").as_array()) {

                path.value<std::string>()
                    .transform([&, this](const std::string& maybe_path_string) {
                        _copy_with.emplace_back(maybe_path_string);
                        return maybe_path_string;
                    });
            }

            for (const toml::node& command: *preset_table.at("execute_in_test_directory").as_array()) {
                const toml::array command_words {command.as_array()};
                std::vector<std::string> command_words_vector {};

                for (const toml::node& word: command_words) {
                    word.value<std::string>()
                        .transform([&](const std::string& maybe_word) {
                            command_words_vector.push_back(maybe_word);
                            return maybe_word;
                        });
                }
            }


        }

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
                    std::string {key_name.substr(0, 7)}, *value.as_table()
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

    configuration_file::copy_and_execute
        configuration_file::files_to_copy_and_execute(const std::vector<std::string>& chosen_presets) const {
        copy_and_execute accumulated_presets {};

        for (const preset& available_preset: _available_presets) {
            for (const std::string& chosen_preset: chosen_presets) {
                if (chosen_preset == available_preset.name()) {
                    accumulated_presets.copy_with.insert(
                            accumulated_presets.copy_with.end(),
                            available_preset.copy_with().cbegin(),
                            available_preset.copy_with().cend()
                    );

                    accumulated_presets.execute_in_test_directory.insert(
                            accumulated_presets.execute_in_test_directory.end(),
                            available_preset.execute_in_test_directory().cbegin(),
                            available_preset.execute_in_test_directory().cend()
                    );
                }
            }
        }

        return accumulated_presets;
    }
}
