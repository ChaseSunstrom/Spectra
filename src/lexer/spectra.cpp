//
// Created by Chase on 10/31/2023.
//

#include <iostream>
#include <string>

#include "spectra.hpp"
#include "scanner.hpp"

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
            std::cout << "Type: " << token::convert_type_to_string(_token.get_type()) << std::endl;
            if (_token.get_literal() != nullptr) {
                std::cout << "Literal: " << _token.get_literal()->convert_value_to_string() << std::endl;
            }
        }
    }

    void spectra::error(uint64_t line, std::string message) {
        spectra::report(line, "", message);
    }

    void spectra::report(uint64_t line, std::string position, std::string message) {
        std::cout << "[LINE " << line << "] Error: " << position << " " << message << std::endl;
    }

    scanner* spectra::get_scanner() {
        return this->_scanner;
    }
}