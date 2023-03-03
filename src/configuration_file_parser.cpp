#include <string>
#include <filesystem>
#include <toml++/toml.h>

#include "./headers/configuration_file_parser.hpp"
#include "toml++/impl/table.h"

namespace tempenv {
    preset::preset(std::string&& name,
            std::vector<std::filesystem::path>&& copy_with,
            std::vector<std::vector<std::string>>&& execute_in_test_directory) :
        _name {name}, _copy_with {copy_with}, _execute_in_test_directory {execute_in_test_directory}
    {}

    preset::preset(std::string&& name, const toml::table& toml_section) :
        _name {name} {

        toml_section["copy_with"].as_array() -> for_each(
            [&, this] (auto&& element) {
                if (element.value<std::string>()) {
                }
            }
        );
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

    configuration_file::configuration_file(const toml::table& parsed_config_file) {
        const std::optional<std::string> maybe_test_path_name {
            parsed_config_file["tests_location"].value<std::string>()
        };

        if (maybe_test_path_name.has_value()) {
            _tests_location = std::filesystem::path {
                maybe_test_path_name.value()};

            _is_valid_tests_location_provided = true;
        }

        else {
            _is_valid_tests_location_provided = false;
        }
    }

    bool configuration_file::is_valid_tests_location_provided() const {
        return _is_valid_tests_location_provided;
    }

    std::filesystem::path configuration_file::tests_location() const {
        return _tests_location;
    }
}
