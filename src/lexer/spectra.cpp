//
// Created by Chase on 10/31/2023.
//

#include <iostream>
#include <string>

#include "spectra.hpp"
#include "scanner.hpp"
#include "../util/debug.hpp"
#include "../ast/expression.hpp"
#include "../parser/parser.hpp"


namespace lex {
    spectra::spectra(bool errored, scanner *scanner) {
        this->_errored = errored;
        this->_scanner = scanner;
    }

    spectra::~spectra() {
    }

    void spectra::run() {
        auto start = FUNCTION_TIME_START()
        std::vector<token> token_list = this->_scanner->scan();
        parse::parser* parser = new parse::parser(token_list);
        ast::expression* expression = parser->parse();
        auto end = FUNCTION_TIME_END()
        PRINT_FUNCTION_TIME(start, end)
        DEBUG_PRINT(parser)
        if (this->_errored) {
            return;
        }
        if (expression) {
            //segfault here
            std::string accepted = expression->accept();
            DEBUG_PRINT(accepted)
        }

        delete parser;
    }

    void spectra::error(uint64_t line, std::string message) {
        REPORT_ERROR(line, message);
    }

    scanner *spectra::get_scanner() {
        return this->_scanner;
    }
}