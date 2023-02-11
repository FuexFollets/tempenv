#include <string>
#include <filesystem>
#include <toml++/toml.h>

#include "./headers/configuration_file_parser.hpp"

namespace tempenv {
    configuration_file::configuration_file(const toml::table& parsed_config_file) {
        const auto maybe_test_path_name {
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
