//
// Created by Chase on 10/31/2023.
//
#include <string>

#include "token.hpp"

namespace lex {
    // namespace lex
    token::token(token_type type, std::string lexeme, uint64_t line, token_data *literal) {
        this->_token_type = type;
        this->_lexeme = std::move(lexeme);
        this->_literal = literal;
        this->line = line;
    }

    token_type token::get_type() {
        return this->_token_type;
    }

    std::string token::get_lexeme() {
        return this->_lexeme;
    }

    token_data *token::get_literal() {
        return this->_literal;
    }

    uint64_t token::get_line() {
        return this->line;
    }

    token_type token::convert_value_to_type(value_type type) {
        switch (type) {
            case value_type::INT:
                return token_type::INT;
            case value_type::FLOAT:
                return token_type::FLOAT;
            case value_type::CHAR:
                return token_type::CHAR;
            case value_type::BOOL:
                return token_type::BOOL;
            case value_type::STRING:
                return token_type::STRING;
            case value_type::VOID:
                return token_type::VOID;
            case value_type::CUSTOM:
                return token_type::CUSTOM;
            default:
                return token_type::NONE;
        }
    }

    std::string token_data::convert_value_to_string() {
        switch (this->_type) {
            case value_type::INT:
                return std::to_string(this->int_value);
            case value_type::FLOAT:
                return std::to_string(this->float_value);
            case value_type::CHAR:
                return std::to_string(this->char_value);
            case value_type::BOOL:
                return std::to_string(this->bool_value);
            case value_type::STRING:
                return this->string_value;
            case value_type::CUSTOM:
                //no way this works, if having errors getting user types later, check this line
                return (char *)this->custom_value;
            default:
                return "";

        }
    }
}