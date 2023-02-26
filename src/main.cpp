#include <cstdlib>
#include <iostream>
#include <functional>
#include <string>

#include "headers/actions.hpp"

int main(int argc, const char** argv) {
    const tempenv::tempenv_argument_parser parsed_arguments {argc, argv};
    const tempenv::decision_maker chosen_options {parsed_arguments};

    tempenv::make_decisions(chosen_options);

    return EXIT_SUCCESS;
}
