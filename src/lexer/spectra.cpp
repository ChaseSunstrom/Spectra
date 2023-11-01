//
// Created by Chase on 10/31/2023.
//

#include <iostream>
#include <string>

#include "spectra.hpp"
#include "scanner.hpp"

namespace lex {
    Spectra::Spectra(bool errored, Scanner* scanner) {
        this->errored = errored;
        this->scanner = scanner;
    }

    Spectra::~Spectra() {
    }
}