#ifndef TEMPENV_CONTEXT_PARSER_HPP

#include <filesystem>
#include <string>

namespace tempenv {
    std::filesystem::path home_directory_path();

    class environment_context {
        std::filesystem::path _most_recent_test_path {};
        std::filesystem::path _path_before_test {};
        bool _is_in_testing_directory {};

        public:

        environment_context();

        [[nodiscard]] std::filesystem::path most_recent_test_path() const;
        [[nodiscard]] std::filesystem::path path_before_test() const;
        [[nodiscard]] bool is_in_testing_directory() const;
    };
}

#endif
