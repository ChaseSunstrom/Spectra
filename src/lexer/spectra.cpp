//
// Created by Chase on 10/31/2023.
//

#include <iostream>
#include <string>
#include <stdexcept>

#include "spectra.hpp"
#include "scanner.hpp"
#include "../util/debug.hpp"
#include "../ast/expression.hpp"
#include "../parser/parser.hpp"
#include "../interpreter/interpreter.hpp"


namespace lex {
    spectra::spectra(bool errored, scanner *scanner) {
        this->_errored = errored;
        this->_scanner = scanner;
        this->_interpreter = new ev::interpreter();
    }

    spectra::~spectra() {
    }

    void spectra::run() {
        auto start = FUNCTION_TIME_START()

        std::vector<token> token_list = this->_scanner->scan();

        for (auto token : token_list) {
            DEBUG_PRINT(convert_type_to_string(token.get_type()))
        }

        parse::parser* parser = new parse::parser(token_list);
        ast::expression* expression = parser->parse();

        auto end = FUNCTION_TIME_END()
        PRINT_FUNCTION_TIME(start, end)

        if (this->_errored) {
            return;
        }

        this->_interpreter->interpret<ast::expression>(expression);

        if (this->_runtime_errored) {
            return;
        }

        delete parser;
    }

    void spectra::error(uint64_t line, std::string message) {
        REPORT_ERROR(line, message)
        _errored = true;
    }

    scanner *spectra::get_scanner() {
        return this->_scanner;
    }
}