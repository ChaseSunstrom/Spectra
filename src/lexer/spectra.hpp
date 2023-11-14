//
// Created by Chase on 10/31/2023.
//

#ifndef SPECTRA_SPECTRA_HPP
#define SPECTRA_SPECTRA_HPP

#include <cstdint>
#include <string>
#include <memory>

#include "scanner.hpp"
#include "../interpreter/interpreter.hpp"

namespace lex {

    extern bool _errored;
    extern bool _runtime_errored;

    class spectra {
    public:
        spectra(scanner* scanner);
        ~spectra();
        void run();
        scanner* get_scanner();
        static void error(uint64_t line, std::string message);
        static void runtime_errored();
    private:
        scanner* _scanner;
    };

}

#endif //SPECTRA_SPECTRA_HPP
