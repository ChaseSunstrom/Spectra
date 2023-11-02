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
    class spectra {
    public:
        spectra(bool errored, scanner* scanner);
        ~spectra();
        void run();
        scanner* get_scanner();
        static void report(uint64_t line, std::string position, std::string message);
        static void error(uint64_t line, std::string message);
    private:
        bool _errored;
        scanner* _scanner;
    };
}

#endif //SPECTRA_SPECTRA_HPP
