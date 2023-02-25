#ifndef TEMPENV_ACTIONS_HPP

#include <filesystem>

#include "decision_maker.hpp"

namespace tempenv {
    void make_decisions(const decision_maker& decisions);

    void make_test_directory(const std::filesystem::path& test_directory_to_be_made);
    void make_tempenv_file(const std::filesystem::path& test_directory_path);
}

#endif
