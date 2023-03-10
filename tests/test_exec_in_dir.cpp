#include <filesystem>
#include <vector>
#include <string>

#include "../src/headers/actions.hpp"

int main() {
    tempenv::execute_in_directory(std::filesystem::path {"."}, std::vector<std::string> {"touch", "hello_word"});
}
