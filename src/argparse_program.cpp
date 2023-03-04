#include <cstdlib>
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
            .help("The name of the test. Will be the name of the directory where the test will be made")
            .required();

        program.add_argument("-i", "--in")
            .help("A path to where the test directory will be made");

        program.add_argument("-c", "--config")
            .help("The path to a different configuration file");

        program.add_argument("-p", "--presets")
            .help("Provide a list of presets to be chosen from the configuration file");
    }

    tempenv_argument_parser::tempenv_argument_parser(int argc, const char** argv) :
        program {"tempenv", "1.0.0"} {
        this -> initialize_program();

        try {
            program.parse_args(argc, argv);
        }

        catch (const std::exception& error) {
            if (!program.is_used("name")) {
                std::cerr
                    << "Error, no argument provided for '--name', '-n'.\n"
                    "Try '--help' for a list of arguments\n"
                    "Exiting.\n";
            }

            else {
                std::cerr << "An error has occurred.\nExiting.";
            }

            exit(128);
        }

        _test_name = program.get<std::string>("--name");

        if (program.is_used("--in")) {
            _test_directory = std::filesystem::path {program.get<std::string>("--in")};
        }

        if (program.is_used("--config")) {
            _configuration_file_location = std::filesystem::path {program.get<std::string>("--config")};
        }

        if (program.is_used("--presets")) {
            _selected_preset_names = program.get<std::vector<std::string>>("--presets");
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
