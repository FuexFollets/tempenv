#ifndef TEMPENV_CONFIGURATION_FILE_PARSER_HPP
#define TEMPENV_CONFIGURATION_FILE_PARSER_HPP
#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include <toml++/toml.h>

namespace tempenv {
    struct preset {
        private:

        std::string _name {};
        std::vector<std::filesystem::path> _copy_with {};
        std::vector<std::vector<std::string>> _execute_in_test_directory {};

        public:

        preset() = default;
        preset(std::string&& name, std::vector<std::filesystem::path>&& copy_with,
               std::vector<std::vector<std::string>>&& execute_in_test_directory);
        explicit preset(std::string&& name, const toml::table& toml_section);

        [[nodiscard]] std::string name() const;
        [[nodiscard]] std::vector<std::filesystem::path> copy_with() const;
        [[nodiscard]] std::vector<std::vector<std::string>> execute_in_test_directory() const;
    };

    class configuration_file {
        private:

        std::filesystem::path _tests_location {};
        bool _is_valid_tests_location_provided {false};
        std::optional<preset> _forall_presets {};
        std::vector<preset> _all_presets {};

        public:

        [[nodiscard]] std::filesystem::path tests_location() const;
        [[nodiscard]] bool is_valid_tests_location_provided() const;
        [[nodiscard]] std::vector<preset> all_presets() const;
        [[nodiscard]] std::optional<preset> forall_presets() const;

        configuration_file() = default;
        explicit configuration_file(const toml::table& parsed_config_file);
    };
} // namespace tempenv

#endif
