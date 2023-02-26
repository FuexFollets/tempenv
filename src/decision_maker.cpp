#include <filesystem>

#include <toml++/toml.h>

#include "headers/defaults.hpp"
#include "headers/decision_maker.hpp"

namespace tempenv {
    decision_maker::decision_maker(const tempenv_argument_parser& parsed_arguments) :
    _test_name {parsed_arguments.test_name()} {
        configuration_file parsed_config_file {};

        if (parsed_arguments.configuration_file_location().has_value()) {
            parsed_config_file = configuration_file {
                toml::parse_file(parsed_arguments
                        .configuration_file_location()
                        .value_or(std::filesystem::path {})
                        .string())
            };
        }

        if (parsed_arguments.test_directory().has_value()) {
            _tests_location = parsed_arguments.test_directory().value_or(std::filesystem::path {});
        }

        else if (parsed_config_file.is_valid_tests_location_provided()) {
            _tests_location = parsed_config_file.tests_location();
        }

        else {
            _tests_location = default_path_for_tests();
        }
    }

    std::filesystem::path decision_maker::tests_location() const {
        return _tests_location;
    }

    std::string decision_maker::test_name() const {
        return _test_name;
    }
}
