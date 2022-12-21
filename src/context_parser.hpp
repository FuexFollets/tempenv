#pragma once

#include <vector>
#include <string_view>
#include <string>
#include <algorithm>
#include <random>

class context_parser {
    public:

    context_parser() = default;
    context_parser(int argc, const char** argv);

    private:
    std::vector<std::string> args_list;

    std::string test_name {}; // Name of directory test is stored in
    std::string test_directory {}; // Name of directory to create directory which the test is store in
    std::string current_directory {}; // Current directory at runtime

    bool is_in_test_directory {};
    bool remove_when_done {};
};

