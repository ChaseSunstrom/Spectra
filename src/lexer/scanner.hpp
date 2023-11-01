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
        Scanner(std::string file_source, std::vector<Token> tokens);
        ~Scanner();
    private:
        std::string _file_source;
        std::vector<Token> _tokens;
        std::map<std::string, TokenType> _keywords;
        uint64_t _current;
        uint64_t _line;
        uint64_t _start;
    };
}

#endif //SPECTRA_SCANNER_HPP
