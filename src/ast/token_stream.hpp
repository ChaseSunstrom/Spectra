
#ifndef SPECTRA_TOKEN_STREAM_HPP
#define SPECTRA_TOKEN_STREAM_HPP

#include <iostream>
#include <lexer/token.hpp>
#include <vector>
namespace ast {

class TokenStream {
   public:
    TokenStream(std::vector<lex::Token>* tokens, uint64_t current);
    ~TokenStream();
    lex::Token* peek();
    lex::Token* previous();
    lex::Token* advance();
    bool is_at_end();
    void error(std::string message);

   private:
    std::vector<lex::Token>* _tokens;
    uint64_t _current;
    uint64_t _line;
    uint64_t _start;
};

}  // namespace ast

#endif  // SPECTRA_SCANNER_HPP