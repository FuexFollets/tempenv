#include <iostream>

#include <toml++/toml.h>

#include "../src/headers/configuration_file_parser.hpp"

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

void print_preset(const tempenv::preset& printed_preset) {
    std::cout << "Preset name: " << printed_preset.name() << '\n'
        << "Preset copy with:\n";

    print_vector(printed_preset.copy_with());

    std::cout << "\nExecute in test directory:\n";

    print_vector(printed_preset.execute_in_test_directory());
}

int main(int argc, const char** argv) {
    if (argc < 2) {
        std::cerr << "Provide path argument.\nExiting.\n";
        exit(128);
    }

    const char* file_path_string {*std::next(argv)};

    tempenv::configuration_file parsed_config_file {toml::parse_file(file_path_string)};

    std::cout << "Parsing file at path: " << file_path_string << '\n';

    std::cout
        << "Is a valid tests location provided? " << parsed_config_file.is_valid_tests_location_provided() << '\n'
        << "If so, test location: " << parsed_config_file.tests_location() << '\n';

    std::cout << "Forall presets\n";
    print_preset(parsed_config_file.forall_presets().value_or(tempenv::preset {}));

    std::cout << "\nAll presets\n";
    for (const tempenv::preset& parsed_preset: parsed_config_file.all_presets()) {
        print_preset(parsed_preset);

        std::cout << '\n';
    }
}
