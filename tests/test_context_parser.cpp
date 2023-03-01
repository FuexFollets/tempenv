#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "../src/headers/context_parser.hpp"

int main() {
    const auto before_test {tempenv::path_before_test()};
    const auto most_recent_test {tempenv::most_recent_test_path()};

    std::cout
        << "Test path before test: " << before_test.value_or(std::filesystem::path {}) << '\n'
        << "Most recent test: " << most_recent_test.value_or(std::filesystem::path {}) << '\n';

    int set_which {};

    std::cout << "Which environment variable should be set? (0: most recent test path, 1: path before test env) ";

    std::cin >> set_which;

    tempenv::set_environment_variable(
        (set_which == 0 ? tempenv::env_variable_names::most_recent_test_path : tempenv::env_variable_names::path_before_test_env),
        std::filesystem::current_path().string().data()
    );

    return EXIT_SUCCESS;
}

