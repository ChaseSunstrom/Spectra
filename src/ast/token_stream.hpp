
#ifndef SPECTRA_TOKEN_STREAM_HPP
#define SPECTRA_TOKEN_STREAM_HPP

#include <iostream>
#include <vector>

#include "../lexer/token.hpp"

namespace ast {
    class token_stream {
    public:
        token_stream(std::vector<lex::token> *tokens, uint64_t current);
        ~token_stream();
        lex::token *peek();
        lex::token *previous();
        lex::token *advance();
        bool is_at_end();
        void error(std::string message);
    private:
        std::vector<lex::token> *_tokens;
        uint64_t _current;
        uint64_t _line;
        uint64_t _start;
    };
}  // namespace ast

#endif  // SPECTRA_SCANNER_HPP