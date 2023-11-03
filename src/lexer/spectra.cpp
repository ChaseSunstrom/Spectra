//
// Created by Chase on 10/31/2023.
//

#include <iostream>
#include <string>

#include "spectra.hpp"
#include "scanner.hpp"
#include "../util/debug.hpp"


namespace lex {
    spectra::spectra(bool errored, scanner* scanner) {
        this->_errored = errored;
        this->_scanner = scanner;
    }

    spectra::~spectra() {
    }

    void spectra::run() {
        std::vector<token> token_list = this->_scanner->scan();
        for (token _token : token_list) {
            DEBUG_PRINT("Type: " << token::convert_type_to_string(_token.get_type()));
            if (_token.get_literal() != nullptr) {
                DEBUG_PRINT("Literal: " << _token.get_literal()->convert_value_to_string());
            }
        }
    }

    void spectra::error(uint64_t line, std::string message) {
        REPORT_ERROR(line, message);
    }

    scanner* spectra::get_scanner() {
        return this->_scanner;
    }
}