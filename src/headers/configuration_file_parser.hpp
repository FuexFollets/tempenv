#ifndef TEMPENV_CONFIGURATION_FILE_PARSER_HPP
#define TEMPENV_CONFIGURATION_FILE_PARSER_HPP
#pragma once

#include <filesystem>

#include <toml++/toml.h>

namespace tempenv {
    class configuration_file {
        private:

        std::filesystem::path _tests_location {};
        bool _is_valid_tests_location_provided {false};

        public:

        [[nodiscard]] std::filesystem::path tests_location() const;
        [[nodiscard]] bool is_valid_tests_location_provided() const;

        configuration_file() = default;
        explicit configuration_file(const toml::table& parsed_config_file);
    };
}

#endif
