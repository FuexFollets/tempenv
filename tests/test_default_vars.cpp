#include <iostream>
#include <string>

#include "../src/headers/defaults.hpp"

int main() {
    std::cout
        << "Default path for tests: " << tempenv::default_path_for_tests() << '\n'
        << "Default configuration path: " << tempenv::default_configuration_path().value_or(std::filesystem::path{}) << '\n';
}
