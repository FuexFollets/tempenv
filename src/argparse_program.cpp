#include <iostream>
#include <stdexcept>
#include <string>
#include <filesystem>

#include <argparse/argparse.hpp>

#include "headers/argparse_program.hpp"

namespace tempenv {
    void tempenv_argument_parser::initialize_program() {
        program.add_argument("-n", "--name")
            .required()
            .help("The name of the test (required). Will be the name of the directory where the test will be made");

        program.add_argument("-i", "--in")
            .help("A path to where the test directory will be made");
    }

    tempenv_argument_parser::tempenv_argument_parser(int argc, const char** argv) :
        program {"tempenv"} {
        this -> initialize_program();

        try {
            program.parse_args(argc, argv);
        } catch (const std::runtime_error& error) {
            std::cerr
                << error.what() << '\n'
                << program << '\n' ;
        }

        _test_name = program.get<std::string>("-n");

        if (program.is_used("-i")) {
            _test_directory = std::filesystem::path {program.get<std::string>("-i")};
        }
    }

    std::string tempenv_argument_parser::test_name() const {
        return _test_name;
    }

    std::optional<std::filesystem::path> tempenv_argument_parser::test_directory() const {
        return _test_directory;
    }
}
