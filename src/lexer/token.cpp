//
// Created by Chase on 10/31/2023.
//
#include "token.hpp"

#include <cstdint>
#include <string>

namespace lex {
 // namespace lex
    token::token(token_type type, std::string lexeme, uint64_t line , token_data* literal) {
        this->_token_type = type;
        this->_lexeme = lexeme;
        this->_literal = literal;
        this->line = line;
    }

    token::~token() {
    }

    token_type token::get_type() {
        return this->_token_type;
    }

    std::string token::get_lexeme() {
        return this->_lexeme;
    }

    token_data* token::get_literal() {
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
            default:
                return token_type::NONE;
        }
    }

    value_type token::convert_type_to_value() {
        switch (this->_token_type) {
            case token_type::INT:
                return value_type::INT;
            case token_type::FLOAT:
                return value_type::FLOAT;
            case token_type::CHAR:
                return value_type::CHAR;
            case token_type::BOOL:
                return value_type::BOOL;
            case token_type::STRING:
                return value_type::STRING;
            case token_type::VOID:
                return value_type::VOID;
            default:
                return value_type::NONE;
        }
    }

    std::string token::convert_type_to_string(token_type type) {
        switch (type) {
            case token_type::LEFT_PAREN:
                return "LEFT_PAREN";
            case token_type::RIGHT_PAREN:
                return "RIGHT_PAREN";
            case token_type::LEFT_BRACE:
                return "LEFT_BRACE";
            case token_type::RIGHT_BRACE:
                return "RIGHT_BRACE";
            case token_type::COMMA:
                return "COMMA";
            case token_type::DOT:
                return "DOT";
            case token_type::TACK:
                return "TACK";
            case token_type::PLUS:
                return "PLUS";
            case token_type::SEMICOLON:
                return "SEMICOLON";
            case token_type::SLASH:
                return "SLASH";
            case token_type::STAR:
                return "STAR";
            case token_type::ASSIGN:
                return "ASSIGN";
            case token_type::BANG:
                return "BANG";
            case token_type::BANG_EQUAL:
                return "BANG_EQUAL";
            case token_type::EQUAL:
                return "EQUAL";
            case token_type::GREATER_THAN:
                return "GREATER_THAN";
            case token_type::GREATER_THAN_EQUAL:
                return "GREATER_THAN_EQUAL";
            case token_type::LESS_THAN:
                return "LESS_THAN";
            case token_type::LESS_THAN_EQUAL:
                return "LESS_THAN_EQUAL";
            case token_type::PIPE:
                return "PIPE";
            case token_type::AMPERSAND:
                return "AMPERSAND";
            case token_type::DOUBLE_PIPE:
                return "DOUBLE_PIPE";
            case token_type::DOUBLE_AMPERSAND:
                return "DOUBLE_AMPERSAND";
            case token_type::IDENT:
                return "IDENT";
            case token_type::DECREMENT:
                return "DECREMENT";
            case token_type::INCREMENT:
                return "INCREMENT";
            case token_type::ADD_ASSIGN:
                return "ADD_ASSIGN";
            case token_type::SUB_ASSIGN:
                return "SUB_ASSIGN";
            case token_type::MUL_ASSIGN:
                return "MUL_ASSIGN";
            case token_type::DIV_ASSIGN:
                return "DIV_ASSIGN";
            case token_type::MOD_ASSIGN:
                return "MOD_ASSIGN";
            case token_type::IF:
                return "IF";
            case token_type::ELSE:
                return "ELSE";
            case token_type::TRUE:
                return "TRUE";
            case token_type::FALSE:
                return "FALSE";
            case token_type::FOR:
                return "FOR";
            case token_type::WHILE:
                return "WHILE";
            case token_type::RETURN:
                return "RETURN";
            case token_type::THIS:
                return "THIS";
            case token_type::STRUCT:
                return "STRUCT";
            case token_type::ENUM:
                return "ENUM";
            case token_type::TYPE:
                return "TYPE";
            case token_type::PUB:
                return "PUB";
            case token_type::PRIV:
                return "PRIV";
            case token_type::SPACE:
                return "SPACE";
            case token_type::IMPL:
                return "IMPL";
            case token_type::BREAK:
                return "BREAK";
            case token_type::CONTINUE:
                return "CONTINUE";
            case token_type::CONST:
                return "CONST";
            case token_type::STATIC:
                return "STATIC";
            case token_type::EXTERN:
                return "EXTERN";
            case token_type::UNION:
                return "UNION";
            case token_type::FN:
                return "FN";
            case token_type::CLASS:
                return "CLASS";
            case token_type::STRING:
                return "STRING";
            case token_type::INT:
                return "INT";
            case token_type::FLOAT:
                return "FLOAT";
            case token_type::CHAR:
                return "CHAR";
            case token_type::BOOL:
                return "BOOL";
            case token_type::VOID:
                return "VOID";
            case token_type::NONE:
                return "NONE";
            case token_type::EOL:
                return "EOL";
            case token_type::ENDOF:
                return "ENDOF";
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
            case value_type::VOID:
                return "void";
            default:
                return "";

        }
    }
}