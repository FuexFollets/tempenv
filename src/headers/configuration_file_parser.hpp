#pragma once

#include <filesystem>
#include <vector>
#include <string>

namespace tempenv {
    struct configuration_file {
        std::filesystem::path tests_location;
        std::vector<std::string> copied_with;
        std::vector<std::vector<std::string>> executed_in_test_directory;

        configuration_file() = default;

        explicit configuration_file(const std::vector<std::string>&);
    };
}

