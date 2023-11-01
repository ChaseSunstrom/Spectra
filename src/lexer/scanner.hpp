//
// Created by Chase on 10/31/2023.
//

#ifndef SPECTRA_SCANNER_HPP
#define SPECTRA_SCANNER_HPP

#include <string>
#include <vector>
#include <map>

#include "token.hpp"

namespace lex {
     class Scanner {
    public:
        Scanner();
        ~Scanner();
    private:
        std::string file_souce;
        std::vector<Token> tokens;
        std::map<std::string, TokenType> keywords;
        uint64_t current;
        uint64_t line;
        uint64_t start;
    };
}

#endif //SPECTRA_SCANNER_HPP
