#include <filesystem>
#include <optional>

namespace tempenv {
    std::filesystem::path default_path_for_tests();
    std::optional<std::filesystem::path> default_configuration_path();
}
