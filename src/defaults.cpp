#include "headers/defaults.hpp"

namespace stdc {
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
}

namespace tempenv {
    std::filesystem::path default_path_for_tests() {
        return std::filesystem::temp_directory_path();
    }

    std::optional<std::filesystem::path> default_configuration_path() {
        std::filesystem::path config_path {};
        config_path /= stdc::getpwuid(stdc::getuid()) -> pw_dir;
        config_path /= ".config/tempenv";

        return std::filesystem::is_directory(config_path) ?
            std::make_optional(config_path) :
            std::optional<std::filesystem::path> {};
    }
}
