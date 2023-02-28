#ifndef TEMPENV_CONTEXT_PARSER_HPP
#define TEMPENV_CONTEXT_PARSER_HPP
#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace tempenv {
    namespace env_variable_names {
        const char* const most_recent_test_path {"__TEMPENV_MOST_RECENT_TEST_PATH"};
        const char* const path_before_test_env {"__TEMPENV_BEFORE_TEST"};
    };

    std::filesystem::path home_directory_path();
    std::optional<std::filesystem::path> most_recent_test_path();
    std::optional<std::filesystem::path> path_before_test();
    bool is_in_testing_directory();

    void set_environment_variable(const char* key, const char* value);
}

#endif
