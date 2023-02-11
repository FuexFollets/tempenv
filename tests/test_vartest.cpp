#include <iostream>
#include <toml++/toml.h>

#include "../src/headers/configuration_file_parser.hpp"

int main() {
    std::cout << std::boolalpha;

    tempenv::configuration_file example_config {toml::parse_file("../example/example_configuration.toml")};

    std::cout
        << "Is a valid tests location provided? " << example_config.is_valid_tests_location_provided() << '\n'
        << "Tests loaction: " << example_config.tests_location() << '\n';

    std::cout << '\n';
}

