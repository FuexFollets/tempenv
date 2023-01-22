#include <fstream>
#include <iostream>
#include <string>
#include <toml.hpp>

// #include "../src/headers/context_parser.hpp"
// #include "../src/headers/configuration_file_parser.hpp"

int main() {
    const std::string toml_file {"example-configuration.toml"};
    const toml::value example_config = toml::parse(toml_file);

    const auto tests_location {toml::find<std::string>(example_config, "tests_location")};

    std::cout << "Location of the tests: " << tests_location << '\n';
}
