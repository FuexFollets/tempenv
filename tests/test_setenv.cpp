#include <cstdlib>

int main() {
    /*
    if (argc < 3) {
        std::cerr << "Invalid number of arguments.\nExiting.\n";
        exit(128);
    }

    setenv(*std::next(argv, 1), *std::next(argv, 3), 0);
    */

    setenv("some_environmen_variable", "abc123", 1);
}
