#include "token_stream.hpp"

namespace ast {

TokenStream::TokenStream(std::vector<lex::Token>* tokens, uint64_t current) {
    this->_tokens = tokens;
    this->_current = current;
    this->_line = 0;
}
TokenStream::~TokenStream() {
}

lex::Token* TokenStream::peek() {
    return &_tokens->at(_current);
}

lex::Token* TokenStream::previous() {
    return &_tokens->at(_current - 1);
}

lex::Token* TokenStream::advance() {
    _current++;
    if (peek()->get_type() == lex::TokenType::EOL) {
        _line++;
    }
    return &_tokens->at(_current);
}

bool TokenStream::is_at_end() {
    return peek()->get_type() == lex::TokenType::ENDOF;
}

void TokenStream::error(std::string message) {
    std::cout << "[line " << _line << "] Error" << message << std::endl;
    throw std::exception();
}

}  // namespace ast
