#include <ios>
#include <iostream>
#include <iterator>
#include <toml++/toml.h>

#include "../src/headers/decision_maker.hpp"

template <typename T> void print_vector(const std::vector<T>& printed_vector) {
    for (const T& value: printed_vector) {
        std::cout << value << " ";
    }
}


template <typename T> void print_vector(const std::vector<std::vector<T>>& printed_vector) {
    for (const std::vector<T>& value: printed_vector) {
        print_vector<T>(value);
        std::cout << '\n';
    }
}


int main(int argc, const char** argv) {
    tempenv::tempenv_argument_parser parsed_arguments {argc, argv};
    tempenv::decision_maker chosen_options {parsed_arguments};

    std::cout << std::boolalpha;

    std::cout
        << "Name of the test: " << chosen_options.test_name() << '\n'
        << "Location of tests: " << chosen_options.tests_location() << '\n';

    std::cout << "\nExecute in test directory commands empty? " << chosen_options.execute_in_test_directory().empty() << '\n';
    print_vector(chosen_options.execute_in_test_directory());

    std::cout << "\nCopy with paths:\n";
    print_vector(chosen_options.copy_with());
}
