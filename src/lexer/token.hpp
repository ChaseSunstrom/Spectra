//
// Created by Chase on 10/31/2023.
//

#ifndef SPECTRA_TOKEN_HPP
#define SPECTRA_TOKEN_HPP

#include <cstdint>
#include <string>
#include <optional>
#include <utility>
#include <any>

#define byte uint8_t

namespace lex {
    enum class token_type{
        NONE = 0,

        //Single Char Tokens
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COMMA,
        DOT,
        TACK,
        PLUS,
        SEMICOLON,
        SLASH,
        STAR,
        ASSIGN,

        //Comparisons
        BANG,
        BANG_EQUAL,
        EQUAL,
        GREATER_THAN,
        GREATER_THAN_EQUAL,
        LESS_THAN,
        LESS_THAN_EQUAL,
        PIPE,
        AMPERSAND,
        DOUBLE_PIPE,
        DOUBLE_AMPERSAND,

        //Literal
        IDENT,
        CUSTOM,

        //Unary
        DECREMENT,
        INCREMENT,

        //Binary
        ADD_ASSIGN,
        SUB_ASSIGN,
        MUL_ASSIGN,
        DIV_ASSIGN,
        MOD_ASSIGN,

        //Keywords
        IF,
        ELSE,
        TRUE,
        FALSE,
        FOR,
        WHILE,
        RETURN,
        THIS,
        STRUCT,
        ENUM,
        TYPE,
        PUB,
        PRIV,
        SPACE,
        IMPL,
        BREAK,
        CONTINUE,
        CONST,
        STATIC,
        EXTERN,
        UNION,
        FN,
        CLASS,
        STRING,
        INT,
        FLOAT,
        CHAR,
        BOOL,
        VOID,

        //EOL
        EOL,

        ENDOF,
    };

    enum class value_type {
        NONE = 0,
        STRING,
        INT,
        FLOAT,
        CHAR,
        BOOL,
        VOID,
        CUSTOM
    };

    struct token_data {
        token_data(value_type type, int value) : _type(type), int_value(value) {};
        token_data(value_type type, double value) : _type(type), float_value(value) {};
        token_data(value_type type, char value) : _type(type), char_value(value) {};
        token_data(value_type type, bool value) : _type(type), bool_value(value) {};
        token_data(value_type type, std::string value) : _type(type), string_value(std::move(value)) {};
        token_data(value_type type, const byte* value) : _type(type), custom_value(value) {};

        std::string convert_value_to_string();

        value_type _type;
        union {
            int int_value;
            double float_value;
            char char_value;
            bool bool_value;
            std::string string_value;
            const byte* custom_value;
        };
    };

    class token {
    public:
        token(token_type type, std::string lexeme, uint64_t line, token_data *literal);
        ~token();
        token_type get_type();
        std::string get_lexeme();
        uint64_t get_line();
        token_data* get_literal();
        static std::string convert_type_to_string(token_type type);
        static token_type convert_value_to_type(value_type type);
        value_type convert_type_to_value();
    private:
        token_type _token_type;
        std::string _lexeme;
        uint64_t line;
        token_data* _literal;
    };
}


#endif //SPECTRA_TOKEN_HPP
