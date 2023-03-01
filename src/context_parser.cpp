#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "./headers/context_parser.hpp"

namespace tempenv {

    std::optional<std::filesystem::path> get_most_recent_test_path() {
        const char* most_recent_test_path_env {std::getenv(env_variable_names::most_recent_test_path)};

        if (most_recent_test_path_env == nullptr) { return {}; }

        return std::filesystem::path {most_recent_test_path_env};
    }

    std::optional<std::filesystem::path> get_path_before_test() {
        const char* path_before_test_env {std::getenv(env_variable_names::path_before_test_env)};

        if (path_before_test_env == nullptr) { return {}; }

        return std::filesystem::path {path_before_test_env};
    }

    bool is_in_testing_directory() {
        return std::filesystem::exists(std::filesystem::current_path() / ".tempenv");
    }

    void set_most_recent_test_path() {
        setenv(env_variable_names::most_recent_test_path,
                std::filesystem::current_path().string().data(), 1);
    }

    void set_path_before_test_env() {
        setenv(env_variable_names::path_before_test_env,
                std::filesystem::current_path().string().data(), 1);
    }


    void set_environment_variables() {
        if (is_in_testing_directory()) {
            set_most_recent_test_path();
        }

        else {
            set_path_before_test_env();
        }
    }
}

