#include <iostream>

#include "../src/headers/actions.hpp"

int main(int argc, const char** argv) {
    tempenv::tempenv_argument_parser parsed_arguments {argc, argv};
    tempenv::configuration_file configuration_file {toml::parse_file("example/example_configuration.toml")};

    tempenv::decision_maker chosen_options {configuration_file, parsed_arguments};

    tempenv::make_decisions(chosen_options);
}
