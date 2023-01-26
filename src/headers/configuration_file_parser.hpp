#pragma once

#include <filesystem>
#include <vector>
#include <toml++/toml.h>

namespace tempenv {
    class configuration_file {

        public:

        struct preset {
            private:

            std::vector<std::filesystem::path> _copy_with {};
            std::vector<std::vector<std::string>> _execute_in_test_directory {};

            public:

            std::vector<std::filesystem::path> copy_with();
            std::vector<std::vector<std::string>> execute_in_test_directory();
        };

        configuration_file() = default;

        [[nodiscard]] bool is_valid_tests_location_provided() const;
        [[nodiscard]] std::filesystem::path tests_location() const;
        [[nodiscard]] std::vector<preset> available_presets() const;

        [[nodiscard]] std::vector<std::filesystem::path> copy_with() const;
        [[nodiscard]] std::vector<std::vector<std::string>> execute_in_test_directory() const;

        private:

        std::filesystem::path _tests_location {};
        bool _is_valid_tests_location_provided {};

        std::vector<preset> _available_presets {};
        preset _forall_presets {};
    };
}

