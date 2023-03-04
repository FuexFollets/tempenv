#include <iostream>

#include <toml++/toml.h>

#include "../src/headers/configuration_file_parser.hpp"

int main() {
    const auto example {
        toml::parse_file("/home/fuexfollets/Projects/tempenv/example/example_configuration.toml")
    };

    for (const auto& path: *example["forall_presets"]["copy_with"].as_array()) {
        std::cout << path.value_or<std::string>({});
    }
}
