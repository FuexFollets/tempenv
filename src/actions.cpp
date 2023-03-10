#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>

#include "headers/actions.hpp"

namespace tempenv {
    void make_decisions(const decision_maker& decisions) {
        if (decisions.default_test_location_chosen() &&
            !std::filesystem::exists(decisions.tests_location())) {
            std::filesystem::create_directory(decisions.tests_location());
        }

        if (!std::filesystem::exists(decisions.tests_location())) {
            std::cerr
                << "Error, directory " << decisions.tests_location()
                << " does not exist.\nExiting.";
            exit(128); // Invalid argument
        }

        if (!std::filesystem::is_directory(decisions.tests_location())) {
            std::cerr
                << "Error, filesystem object " << decisions.tests_location()
                << " exists but is not a directory.\nExiting";
            exit(128); // Invalid argument
        }

        const auto directory_to_be_made {decisions.tests_location() / decisions.test_name()};

        if (std::filesystem::exists(directory_to_be_made)) {
            std::cerr
                << "Error, filesystem object already exists at path "
                << directory_to_be_made << ".\nExiting.";
            exit(128); // Invalid argument
        }

        make_test_directory(directory_to_be_made);
        make_tempenv_file(directory_to_be_made);

        std::cout << directory_to_be_made.string() << '\n';
    }

    void make_test_directory(const std::filesystem::path& test_directory_to_be_made) {
        std::filesystem::create_directories(test_directory_to_be_made);
    }

    void make_tempenv_file(const std::filesystem::path& test_directory_path) {
        std::ofstream {test_directory_path / ".tempenv"}.close();
    }

    void execute_in_directory(const std::filesystem::path& test_directory_path,
            const std::vector<std::string>& command) {
        std::filesystem::current_path(test_directory_path);

        static const std::function<std::string(std::string&&, const std::string&)> fold_space {
            [] (std::string&& first, const std::string& second) -> std::string {
                return std::move(first) + " " + second;
            }
        };

        std::system(
            std::accumulate(command.begin(), command.end(), std::string {}, fold_space).c_str()
        );
    }
}
