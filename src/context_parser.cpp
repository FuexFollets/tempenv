#include <cstdlib>
#include <cstring>
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

    void set_environment_variable(const char* key, const char* value) {
        using namespace std::string_literals;

        putenv((
            std::string {key} +
            "="s +
            std::string {value}).data()
        );
    }

    void set_environment_variables() {
        using namespace std::string_literals;

        set_environment_variable(
            is_in_testing_directory() ? env_variable_names::most_recent_test_path : env_variable_names::path_before_test_env,
            std::filesystem::current_path().string().data());
    }
}

