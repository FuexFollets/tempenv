#ifndef TEMPENV_DECISION_MAKER_HPP

#include <filesystem>
#include <string>

#include <argparse/argparse.hpp>
#include <toml++/toml.h>

#include "configuration_file_parser.hpp"
#include "argparse_program.hpp"
#include "defaults.hpp"

namespace tempenv {
    class decision_maker {
        private:

        std::filesystem::path _tests_location {};
        std::string _test_name {};

        public:

        [[nodiscard]] std::filesystem::path tests_location() const;
        [[nodiscard]] std::string test_name() const;

        decision_maker(const configuration_file& parsed_config_file, const tempenv_argument_parser& parsed_arguments);
    };
}

#endif
