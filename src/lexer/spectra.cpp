//
// Created by Chase on 10/31/2023.
//

#include <iostream>
#include <string>
#include <memory>

#include "spectra.hpp"
#include "scanner.hpp"
#include "../util/debug.hpp"
#include "../ast/expression.hpp"


namespace lex {
    spectra::spectra(bool errored, scanner *scanner) {
        this->_errored = errored;
        this->_scanner = scanner;
    }

    spectra::~spectra() {
    }

    void spectra::run() {
        std::vector<token> token_list = this->_scanner->scan();
        for (token _token: token_list) {
            DEBUG_PRINT("Type: " << token::convert_type_to_string(_token.get_type()))
            if (_token.get_literal() != nullptr) {
                DEBUG_PRINT("Literal: " << _token.get_literal()->convert_value_to_string())
            }
        }
#ifdef DEBUG
        ast::expression *expr = new ast::binary_expression(
                std::make_shared<ast::unary_expression>(
                        ast::unary_expression(
                                std::make_shared<token>(
                                        token(token_type::TACK, "-", 1, nullptr)),
                                std::make_shared<ast::literal_expression<token_data>>(
                                        new token_data(value_type::INT, 123)
                                ))
                ),
                std::make_shared<token>(token_type::STAR, "*", 1, nullptr),
                std::make_shared<ast::grouping_expression>(
                        std::make_shared<ast::literal_expression<token_data>>(
                                new token_data(value_type::INT, 456)
                        )
                )
        );

        ast::print_expression(expr);
#endif
    }

    void spectra::error(uint64_t line, std::string message) {
        REPORT_ERROR(line, message);
    }

    scanner *spectra::get_scanner() {
        return this->_scanner;
    }
}