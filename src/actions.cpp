#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "headers/actions.hpp"

namespace tempenv {
    void make_decisions(const decision_maker& decisions) {
        if (!std::filesystem::is_directory(decisions.tests_location())) {
            std::cerr
                << "Error, directory '" << decisions.tests_location()
                << "' does not exist. Exiting";
            exit(128); // Invalid argument
        }


        const auto directory_to_be_made {decisions.tests_location() / decisions.test_name()};

        if (std::filesystem::exists(directory_to_be_made)) {
            std::cerr
                << "Error, file system object already exists at path '"
                << directory_to_be_made << "'. Exiting";
            exit(128); // Invalid argument
        }

        make_test_directory(directory_to_be_made);
    }

    void make_test_directory(const std::filesystem::path& test_directory_to_be_made) {
        std::cout
            << "Make test directory called where: "
            << '\t' << "test_directory_to_be_made = " << test_directory_to_be_made << '\n';
    }
}
