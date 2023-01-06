#include <filesystem>
#include <cstring>
#include <cstdlib>
#include <string>
#include <ios>
#include <fstream>

#include <stdlib.h>

#include "context_parser.hpp"

namespace tempenv {
    namespace env_variable_names {
        const char* const last_test_path {"__TEMPENV_BEFORE_TEST_PATH"};
        const char* const last_working_directory {"__TEMPENV_BEFORE_TEST_PATH"};
        const char* const configuration_directory {"XDG_CONFIG_HOME"};
    };


    environment_context::environment_context() {
        const std::filesystem::path current_path {std::filesystem::current_path()};

        environment_variables.last_test_path = std::getenv(env_variable_names::last_test_path);
        environment_variables.last_working_directory = std::getenv(env_variable_names::last_working_directory);

        std::filesystem::path tempenv_dotfile_path {current_path};
        tempenv_dotfile_path /= ".tempenv";

        environment_files.is_in_testing_directory = std::filesystem::exists(tempenv_dotfile_path);

        if (!environment_files.is_in_testing_directory) { // Set `environment_variables.last_working_directory`
            std::string environment_variable_setting_string {};

            environment_variable_setting_string +=
                std::string {env_variable_names::last_working_directory} +
                std::string {"="} +
                current_path.string();

            putenv(environment_variable_setting_string.data());
        }

        std::filesystem::path configuration_path {std::getenv(env_variable_names::configuration_directory)};
        configuration_path /= ".tempenv";
        configuration_path /= ".tempenv.conf";

        environment_files.config_file_exists = std::filesystem::exists(configuration_path);

        if (environment_files.config_file_exists) { // Read configuration file `$XDG_CONFIG_HOME/tempenv/tempenv.conf`
            environment_files.config_directory_path = configuration_path;

            std::ifstream file_contents_stream {configuration_path, std::ios::in};

            file_contents_stream >> environment_files.config_file_contents;

            file_contents_stream.close();
        }
    }
}

