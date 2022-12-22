#pragma once

#include <cstddef>
#include <type_traits>
#include <vector>
#include <string_view>
#include <string>
#include <algorithm>
#include <random>
#include <span>
#include <concepts>

namespace tempenv { namespace constraints {
        template <typename T, typename type_constructed>
        concept can_construct = std::is_constructible<type_constructed, T>::value;
    }

    struct option {
        option() = default;
        option(const option&) = default;

        option(constraints::can_construct<std::string> auto, constraints::can_construct<std::string> auto);
        option(constraints::can_construct<std::string> auto, option*);

        const std::string_view name;
        const std::string_view description;

        bool is_same_as_another {};
        const option* same_option {nullptr};
    };

    static constexpr const std::size_t available_option_count {};
    static constexpr const std::array<option, available_option_count> all_options {};

    class context_parser {
        public:

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

    option::option(
            constraints::can_construct<std::string> auto option_name,
            constraints::can_construct<std::string> auto option_description) :
        name {std::move(option_name)}, description {std::move(option_description)} {}

    option::option(
            constraints::can_construct<std::string> auto option_name,
            option* option_same_as_this) : name {std::move(option_name)}, is_same_as_another {true}, same_option {option_same_as_this} {
        option_same_as_this -> is_same_as_another = true;
        option_same_as_this -> same_option = this;
    }
}

