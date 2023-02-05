#include <fstream>
#include <iostream>
#include <string>
#include <toml++/toml.h>

int main() {
    const auto example {
        toml::parse_file("/home/fuexfollets/Projects/tempenv/example/example_configuration.toml")};

    /*
    std::cout << "Parsed toml file: \n"
        << example << "\n\n";
    */

    std::cout
        << "Tests location: " << example["tests_location"] << '\n'
        << "Presets forall: "
        << example["forall_presets"]["execute_in_test_directory"][0][0] << '\n';

}
