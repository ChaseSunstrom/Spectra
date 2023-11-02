//
// Created by Chase on 10/31/2023.
//
#include "token.hpp"

#include <cstdint>
#include <string>

namespace lex {
Token::Token(TokenType type, std::string lexeme, uint64_t line, void* literal) {
    this->token_type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
};

Token::~Token() {
}

TokenType Token::get_type() {
    return this->token_type;
}

}  // namespace lex