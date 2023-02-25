#include <iostream>
#include <toml++/toml.h>

#include "../src/headers/decision_maker.hpp"

int main(int argc, const char** argv) {
    tempenv::tempenv_argument_parser parsed_arguments {argc, argv};
    tempenv::configuration_file configuration_file {toml::parse_file("example/example_configuration.toml")};

    tempenv::decision_maker chosen_options {configuration_file, parsed_arguments};

    std::cout
        << "Name of the test: " << chosen_options.test_name() << '\n'
        << "Location of tests: " << chosen_options.tests_location() << '\n';
}
