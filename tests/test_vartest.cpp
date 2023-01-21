#include <iostream>
#include <string>
#include <iterator>

#include "../src/headers/context_parser.hpp"
#include "../src/headers/configuration_file_parser.hpp"

int main() {
    std::cout << std::boolalpha;
    tempenv::environment_context env_context {};

    tempenv::configuration_file configuration_file {
        env_context.config_file_contents(),
        std::vector<std::string>{"hello"}
    };

    std::cout << "Environent conetext tests: \n\n"
        << "Home directory: " << tempenv::home_directory_path() << '\n'
        << "Are we in a testing directory? " << env_context.is_in_testing_directory() << '\n'
        << "Configuration directory path: " << env_context.config_directory_path() << '\n'
        << "Path to most recent test: " << env_context.last_test_path() << '\n'
        << "Path to working directory before in current test: " << env_context.last_working_directory() << '\n'
        << "Does the configuration file exist? " << env_context.config_file_exists() << '\n'
        << "Contents of the config file: \n" << env_context.config_file_contents() << '\n';

    auto copy_with {configuration_file.copy_with()};
    auto invalid_presets {configuration_file.invalid_presets()};

    std::cout << "\n\nConfiguration file tests: \n\n";
    std::cout << "Files to copy with: ";
    std::copy(
            copy_with.begin(), copy_with.end(),
            std::ostream_iterator<std::string>(std::cout, ", "));


    std::cout
        << "\nIs a valid tests location specified? " << configuration_file.is_valid_tests_location_provided()
        << "\nTests location: " << configuration_file.tests_location()
        << "\nInvalid presets: ";

    std::copy(
            invalid_presets.begin(), invalid_presets.end(),
            std::ostream_iterator<std::string>(std::cout, ", "));

    std::cout << "\nExecuted in directory: ";
    for (auto&& command: configuration_file.execute_in_test_directory()) {
        std::copy(
                command.begin(), command.end(),
                std::ostream_iterator<std::string>(std::cout, ", "));
    }

    std::cout << '\n';
}

