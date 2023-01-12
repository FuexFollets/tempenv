#include <iostream>
#include <functional>

#include "./headers/context_parser.hpp"
#include "./headers/configuration_file_parser.hpp"

int main() {
    tempenv::environment_context env_context {};

    std::cout << std::boolalpha;

    std::cout
        << "Home directory: " << tempenv::home_directory_path() << '\n'
        << "Are we in a testing directory? " << env_context.is_in_testing_directory() << '\n'
        << "Available temp directory path: " << env_context.temp_directory_path() << '\n'
        << "Configuration directory path: " << env_context.config_directory_path() << '\n'
        << "Path to most recent test: " << env_context.last_test_path() << '\n'
        << "Path to working directory before in current test: " << env_context.last_working_directory() << '\n'
        << "Does the configuration file exist? " << env_context.config_file_exists() << '\n'
        << "Contents of the config file: \n" << env_context.config_file_contents() << '\n';
}


