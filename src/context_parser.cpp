#include <filesystem>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ios>
#include <fstream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <stdlib.h>

#include "./headers/context_parser.hpp"

namespace tempenv {
    namespace env_variable_names {
        const char* const most_recent_test_path {"__TEMPENV_MOST_RECENT_TEST_PATH"};
        const char* const path_before_test_env {"__TEMPENV_BEFORE_TEST"};
    };

    environment_context::environment_context() {
        const std::filesystem::path current_path {std::filesystem::current_path()};

        const char* most_recent_test_path_env {std::getenv(env_variable_names::most_recent_test_path)};
        const char* path_before_test_env {std::getenv(env_variable_names::path_before_test_env)};

        if (most_recent_test_path_env != nullptr) {
            _most_recent_test_path = std::filesystem::path {most_recent_test_path_env};
        }

        if (path_before_test_env != nullptr) {
            _path_before_test = std::filesystem::path {path_before_test_env};
        }

        _is_in_testing_directory = std::filesystem::exists(current_path / ".tempenv");

        if (!_is_in_testing_directory) {
            std::string environment_variable_setting_string {
                std::string {env_variable_names::path_before_test_env} +
                std::string {"="} +
                current_path.string()
            };

            putenv(environment_variable_setting_string.data());
        }

        else {
            std::string environment_variable_setting_string {
                std::string {env_variable_names::most_recent_test_path} +
                std::string {"="} +
                current_path.string()
            };

            putenv(environment_variable_setting_string.data());
        }
    }

    std::filesystem::path environment_context::most_recent_test_path() const {
        return _most_recent_test_path;
    }

    std::filesystem::path environment_context::path_before_test() const {
        return _path_before_test;
    }

    bool environment_context::is_in_testing_directory() const {
        return _is_in_testing_directory;
    }
}

