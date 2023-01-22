#include <string>
#include <toml.hpp>

#include "./headers/configuration_file_parser.hpp"

namespace tempenv {
    configuration_file::configuration_file(const toml::value& parsed_toml) {
        const auto& presets {toml::find(parsed_toml, "presets")};
    }
}
