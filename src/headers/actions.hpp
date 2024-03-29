#ifndef TEMPENV_ACTIONS_HPP
#define TEMPENV_ACTIONS_HPP
#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "decision_maker.hpp"

namespace tempenv {
    void make_decisions(const decision_maker& decisions);

    void make_test_directory(const std::filesystem::path& test_directory_to_be_made);
    void make_tempenv_file(const std::filesystem::path& test_directory_path);
    void execute_in_directory(const std::filesystem::path& test_directory_path,
                              const std::vector<std::string>& command);
} // namespace tempenv

#endif
