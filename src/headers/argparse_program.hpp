#include <optional>
#include <string>
#include <filesystem>

#include <argparse/argparse.hpp>

namespace tempenv {
    class tempenv_argument_parser {
        private:

        std::string _test_name;
        std::optional<std::filesystem::path> _test_directory;

        argparse::ArgumentParser program;

        public:

        [[nodiscard]] std::string test_name() const;
        [[nodiscard]] std::optional<std::filesystem::path> test_directory() const;
    };
}
