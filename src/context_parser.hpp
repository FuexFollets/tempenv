#pragma once

#include <cstddef>
#include <vector>
#include <string_view>
#include <string>
#include <algorithm>
#include <random>
#include <span>
#include <concepts>

namespace constraints {
    template <typename T, typename type_constructed>
    concept can_construct = requires(T value) {
        type_constructed(value);
    };
}

class context_parser {
    public:

    static constexpr const std::size_t available_option_count {};

    struct option {
        option(const option&) = default;

        option(constraints::can_construct<std::string> auto, constraints::can_construct<std::string> auto);
        option(constraints::can_construct<std::string> auto, option*);

        const std::string_view name;
        const std::string_view description;

        bool is_same_as_another {};
        const option* const same_option;
    };

    static constexpr const std::array<option, available_option_count> all_options {};

    context_parser() = default;
    context_parser(int argc, const char** argv);

    private:
    std::vector<std::string> args_list;

    std::string test_name {}; // Name of directory test is stored in
    std::string test_path {}; // Path to the directory in which the test directory will be stored (defaults to $home/tests)
    std::string current_directory {}; // Current directory at runtime

    bool is_in_test_directory {};
    bool remove_when_done {};
};
