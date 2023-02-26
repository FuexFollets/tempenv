#include <exception>
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
            .help("The name of the test. Will be the name of the directory where the test will be made");

        program.add_argument("-i", "--in")
            .help("A path to where the test directory will be made");

        program.add_argument("-c", "--config")
            .help("The path to a different configuration file");
    }

    tempenv_argument_parser::tempenv_argument_parser(int argc, const char** argv) :
        program {"tempenv"} {
        this -> initialize_program();

        try {
            program.parse_args(argc, argv);
        }

        catch (const std::exception& error) {
            std::cerr
                << "Error, no argument provided for '--name', '-n'.\n"
                   "Try '--help' for a list of arguments\n"
                   "Exiting.\n";
            exit(128);
        }

        _test_name = program.get<std::string>("-n");

        if (program.is_used("-i")) {
            _test_directory = std::filesystem::path {program.get<std::string>("-i")};
        }

        if (program.is_used("-c")) {
            _configuration_file_location = std::filesystem::path {program.get<std::string>("-c")};
        }
    }

    std::string tempenv_argument_parser::test_name() const {
        return _test_name;
    }

    std::optional<std::filesystem::path> tempenv_argument_parser::test_directory() const {
        return _test_directory;
    }

    std::optional<std::filesystem::path> tempenv_argument_parser::configuration_file_location() const {
        return _configuration_file_location;
    }
}
