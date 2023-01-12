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
        const char* const last_test_path {"__TEMPENV_BEFORE_TEST_PATH"};
        const char* const last_working_directory {"__TEMPENV_BEFORE_TEST_PATH"};
        const char* const configuration_directory {"XDG_CONFIG_HOME"};
    };

    environment_context::environment_context() {
        const std::filesystem::path current_path {std::filesystem::current_path()};

        const char* last_test_path_env {std::getenv(env_variable_names::last_test_path)};
        const char* last_working_directory_env {std::getenv(env_variable_names::last_working_directory)};

        if (last_test_path_env != nullptr) { _last_test_path = last_test_path_env; }
        if (last_working_directory_env != nullptr) { _last_working_directory = last_working_directory_env; }

        std::filesystem::path tempenv_dotfile_path {current_path};
        tempenv_dotfile_path /= ".tempenv";

        _is_in_testing_directory = std::filesystem::exists(tempenv_dotfile_path);

        if (!_is_in_testing_directory) { // Set `_last_working_directory`
            std::string environment_variable_setting_string {};

            environment_variable_setting_string +=
                std::string {env_variable_names::last_working_directory} +
                std::string {"="} +
                current_path.string();

            putenv(environment_variable_setting_string.data());
        }

        std::filesystem::path configuration_path {};
        const char* configuration_path_env {std::getenv(env_variable_names::configuration_directory)};

        if (configuration_path_env == nullptr) {
            auto *const home {getpwuid(getuid())};
            configuration_path = home -> pw_dir; // Home directory path string
            configuration_path /= ".config";
        } else {
            configuration_path = configuration_path_env;
        }

        configuration_path /= "tempenv";
        configuration_path /= ".tempenv.conf";

        _config_file_exists = std::filesystem::exists(configuration_path);

        if (_config_file_exists) { // Read configuration file `$XDG_CONFIG_HOME/tempenv/tempenv.conf`
            _config_directory_path = configuration_path;
            std::ifstream file_contents_stream {configuration_path, std::ios::in};

            file_contents_stream >> _config_file_contents;
        }
    }


    std::filesystem::path environment_context::last_test_path() const {
        return _last_test_path;
    }


    std::filesystem::path environment_context::last_working_directory() const {
        return _last_working_directory;
    }


    std::filesystem::path environment_context::config_directory_path() const {
        return _config_directory_path;
    }


    std::filesystem::path environment_context::temp_directory_path() const {
        return _temp_directory_path;
    }


    std::string environment_context::config_file_contents() const {
        return _config_file_contents;
    }


    bool environment_context::config_file_exists() const {
        return _config_file_exists;
    }


    bool environment_context::is_in_testing_directory() const {
        return _is_in_testing_directory;
    }
}

