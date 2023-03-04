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

    std::cout << '\n';

    const auto& all_presets {example["presets"]};

    std::cout << "All presets:\n" << all_presets << '\n';

    for (auto&&[preset_name, value]: *all_presets.as_table()) {
        std::cout
            << "Preset name: " << preset_name << '\n'
            << "Preset value:\n" << *value.as_table() << "\n\n\n";
    }
}
