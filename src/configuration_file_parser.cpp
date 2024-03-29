#include <filesystem>
#include <string>

#include <toml++/toml.h>

#include "./headers/configuration_file_parser.hpp"
#include "toml++/impl/node.h"
#include "toml++/impl/table.h"

namespace tempenv {
    preset::preset(std::string&& name, std::vector<std::filesystem::path>&& copy_with,
                   std::vector<std::vector<std::string>>&& execute_in_test_directory) :
        _name {name},
        _copy_with {copy_with}, _execute_in_test_directory {execute_in_test_directory} {
    }

    preset::preset(std::string&& name, const toml::table& toml_section) : _name {name} {
        if (toml_section ["copy_with"].is_array()) {
            for (const toml::node& maybe_file_path: *toml_section ["copy_with"].as_array()) {
                if (const std::optional<std::string> path = maybe_file_path.value<std::string>()) {
                    _copy_with.emplace_back(path.value());
                }
            }
        }

        for (const toml::node& maybe_command:
             *toml_section ["execute_in_test_directory"].as_array()) {
            if (!maybe_command.is_array()) {
                continue;
            }

            std::vector<std::string> command_words {};

            for (const toml::node& maybe_command_word: *maybe_command.as_array()) {
                if (const std::optional<std::string> command_word =
                        maybe_command_word.value<std::string>()) {
                    command_words.emplace_back(command_word.value());
                }
            }

            _execute_in_test_directory.emplace_back(std::move(command_words));
        }
    }

    std::string preset::name() const {
        return _name;
    }

    std::vector<std::filesystem::path> preset::copy_with() const {
        return _copy_with;
    }

    std::vector<std::vector<std::string>> preset::execute_in_test_directory() const {
        return _execute_in_test_directory;
    }

    configuration_file::configuration_file(const toml::table& parsed_config_file) :
        _forall_presets {
            preset {std::string {}, *parsed_config_file ["forall_presets"].as_table()}
    } {
        const std::optional<std::string> maybe_test_path_name {
            parsed_config_file ["tests_location"].value<std::string>()};

        if (maybe_test_path_name.has_value()) {
            _tests_location = std::filesystem::path {maybe_test_path_name.value()};

            _is_valid_tests_location_provided = true;
        }

        else {
            _is_valid_tests_location_provided = false;
        }

        for (auto&& [name, value]: *parsed_config_file ["presets"].as_table()) {
            _all_presets.push_back(preset {std::string {name.str()}, *value.as_table()});
        }
    }

    bool configuration_file::is_valid_tests_location_provided() const {
        return _is_valid_tests_location_provided;
    }

    std::filesystem::path configuration_file::tests_location() const {
        return _tests_location;
    }

    std::vector<preset> configuration_file::all_presets() const {
        return _all_presets;
    }

    std::optional<preset> configuration_file::forall_presets() const {
        return _forall_presets;
    }
} // namespace tempenv
