#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "headers/actions.hpp"

namespace tempenv {
    void make_decisions(const decision_maker& decisions) {
        if (!std::filesystem::is_directory(decisions.tests_location())) {
            std::cerr
                << "Error, directory " << decisions.tests_location()
                << " does not exist.\nExiting.";
            exit(128); // Invalid argument
        }


        const auto directory_to_be_made {decisions.tests_location() / decisions.test_name()};

        if (std::filesystem::exists(directory_to_be_made)) {
            std::cerr
                << "Error, file system object already exists at path "
                << directory_to_be_made << ".\nExiting.";
            exit(128); // Invalid argument
        }

        make_test_directory(directory_to_be_made);
        make_tempenv_file(directory_to_be_made);

        std::cout << directory_to_be_made.string() << '\n';
    }

    void make_test_directory(const std::filesystem::path& test_directory_to_be_made) {
        std::filesystem::create_directory(test_directory_to_be_made);
    }

    void make_tempenv_file(const std::filesystem::path& test_directory_path) {
        std::ofstream {test_directory_path / ".tempenv"}.close();
    }
}
