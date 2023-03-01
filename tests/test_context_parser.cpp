#include <cstdlib>
#include <filesystem>
#include <ios>
#include <iostream>

#include "../src/headers/context_parser.hpp"

int main() {
    const auto before_test {tempenv::get_path_before_test()};
    const auto most_recent_test {tempenv::get_most_recent_test_path()};

    std::cout << std::boolalpha;

    std::cout
        << "Test path before test: " << before_test.value_or(std::filesystem::path {}) << '\n'
        << "Most recent test: " << most_recent_test.value_or(std::filesystem::path {}) << '\n'
        << "Is the current directory a testing directory? " << tempenv::is_in_testing_directory() << '\n';

    int set_choice {};

    std::cout << "Which environment variable should be set? (0: most recent test path, 1: other env) ";

    std::cin >> set_choice;

    if (set_choice == 0) {
        tempenv::set_most_recent_test_path();
    }

    if (set_choice == 1) {
        tempenv::set_path_before_test_env();
    }

    return EXIT_SUCCESS;
}

