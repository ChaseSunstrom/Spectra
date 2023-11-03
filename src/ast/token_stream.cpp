#include "token_stream.hpp"

#include "../util/debug.hpp"

namespace ast {

    token_stream::token_stream(std::vector<lex::token> *tokens, uint64_t current) {
        this->_tokens = tokens;
        this->_current = current;
        this->_line = 0;
    }

    token_stream::~token_stream() {
    }

    lex::token *token_stream::peek() {
        return &_tokens->at(_current);
    }

    lex::token *token_stream::previous() {
        return &_tokens->at(_current - 1);
    }

    lex::token *token_stream::advance() {
        _current++;
        if (peek()->get_type() == lex::token_type::EOL) {
            _line++;
        }
        return &_tokens->at(_current);
    }

    bool token_stream::is_at_end() {
        return peek()->get_type() == lex::token_type::ENDOF;
    }

    void token_stream::error(std::string message) {
        REPORT_ERROR(this->_line, message);
    }
}  // namespace ast
