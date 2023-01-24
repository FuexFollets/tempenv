#include <fstream>
#include <iostream>
#include <string>
#include <toml++/toml.h>

int main() {
    const auto example {toml::parse_file("./example.toml")};

    std::cout << "Tests location: " << example["tests_location"];
}
