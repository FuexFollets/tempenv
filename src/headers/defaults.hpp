#ifndef TEMPENV_DEFAULTS_HPP
#define TEMPENV_DEFAULTS_HPP
#pragma once

#include <filesystem>
#include <optional>

namespace tempenv {
    std::filesystem::path default_path_for_tests();
    std::filesystem::path default_configuration_path();
} // namespace tempenv

#endif
