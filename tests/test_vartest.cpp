#include <iostream>
#include <toml++/toml.h>

#include "../src/headers/context_parser.hpp"
#include "../src/headers/configuration_file_parser.hpp"

int main() {
    std::cout << std::boolalpha;

    tempenv::configuration_file example_config {toml::parse_file("./example.toml")};
    std::vector<std::string> chosen_presets {};
    const auto[copy_with, execute_in_test] {example_config.files_to_copy_and_execute(chosen_presets)};

    std::cout
        << "Is a valid test location provided? " << example_config.is_valid_tests_location_provided() << '\n'
        << "Valid tests location: " << example_config.tests_location() << '\n';

    std::cout << '\n';
}

