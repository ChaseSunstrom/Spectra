//
// Created by Chase on 10/31/2023.
//

#include <iostream>
#include <memory>
#include <string>

#include "spectra.hpp"

namespace lex {
    Spectra::Spectra(bool errored, std::unique_ptr<Scanner> scanner) {
        this->errored = errored;
        this->scanner = std::move(scanner);
    }

    Spectra::~Spectra() {
    }
}