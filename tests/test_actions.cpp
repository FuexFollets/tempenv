#include <iostream>

#include "../src/headers/actions.hpp"

int main(int argc, const char** argv) {
    tempenv::tempenv_argument_parser parsed_arguments {argc, argv};
    tempenv::decision_maker chosen_options {parsed_arguments};

    tempenv::make_decisions(chosen_options);
}
