#include <iostream>

#include "../src/headers/argparse_program.hpp"

int main(int argc, const char** argv) {
    tempenv::tempenv_argument_parser argparser {argc, argv};

    std::cout
        << "Test name: " << argparser.test_name() << '\n'
        << "Directory where the test will be made: " << argparser.test_directory().value_or("test directory not provided");
}
