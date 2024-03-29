#include "headers/defaults.hpp"

namespace stdc {
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
} // namespace stdc

namespace tempenv {
    std::filesystem::path default_path_for_tests() {
        return std::filesystem::temp_directory_path() / "tempenv";
    }

    std::filesystem::path default_configuration_path() {
        std::filesystem::path config_path {};
        config_path /= stdc::getpwuid(stdc::getuid())->pw_dir;
        config_path /= ".config/tempenv";

        return config_path;
    }
} // namespace tempenv
