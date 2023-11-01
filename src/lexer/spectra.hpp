//
// Created by Chase on 10/31/2023.
//

#ifndef SPECTRA_SPECTRA_HPP
#define SPECTRA_SPECTRA_HPP

#include <cstdint>
#include <string>
#include <memory>

#include "scanner.hpp"

namespace lex {
    class Spectra {
    public:
        Spectra(bool errored, std::unique_ptr<Scanner> scanner);
        ~Spectra();
        void run();
        void report(uint64_t line, std::string position, std::string message);
        void error(uint64_t line, std::string message);
    private:
        bool errored;
        std::unique_ptr<Scanner> scanner;
    };
}

#endif //SPECTRA_SPECTRA_HPP
