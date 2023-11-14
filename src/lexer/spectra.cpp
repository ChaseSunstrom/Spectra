//
// Created by Chase on 10/31/2023.
//

#include <iostream>
#include <string>
#include <stdexcept>


#include "../interpreter/interpreter.hpp"
#include "spectra.hpp"
#include "scanner.hpp"
#include "../util/debug.hpp"
#include "../ast/expression.hpp"
#include "../parser/parser.hpp"


namespace lex {
    bool _errored = false;
    bool _runtime_errored = false;

    spectra::spectra(scanner *scanner) {
        this->_scanner = scanner;
    }

    spectra::~spectra() {
        delete this->_scanner;
    }

    void spectra::run() {
        auto start = FUNCTION_TIME_START()

        std::vector<token> token_list = this->_scanner->scan();

        for (auto token : token_list) {
            DEBUG_PRINT(convert_type_to_string(token.get_type()))
            if (token.get_literal()) {
                std::cout << token.get_literal()->convert_value_to_string() << std::endl;
            }
        }

        parse::parser* parser = new parse::parser(token_list);
        //parser does not make proper expressions, WHY????
        ast::expression* expression = parser->parse();

        DEBUG_PRINT(expression->accept())

        auto end = FUNCTION_TIME_END()
        PRINT_FUNCTION_TIME(start, end)

        //if (_errored) {
        //    return;
        //}

        inter::interpreter* interpreter = new inter::interpreter();
        interpreter->interpret<ast::expression*>(expression);

        if (_runtime_errored) {
            return;
        }
    }

    void spectra::error(uint64_t line, std::string message) {
        REPORT_ERROR(line, message)
        _errored = true;
    }

    void spectra::runtime_errored() {
        _runtime_errored = true;
    }

    scanner *spectra::get_scanner() {
        return this->_scanner;
    }
}