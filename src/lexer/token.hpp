//
// Created by Chase on 10/31/2023.
//

#ifndef SPECTRA_TOKEN_HPP
#define SPECTRA_TOKEN_HPP

#include <cstdint>
#include <string>
#include <optional>

namespace lex {
    enum class TokenType {
        //Single Char Tokens
        LeftParen,
        RightParen,
        LeftBrace,
        RightBrace,
        Comma,
        Dot,
        Tack,
        Plus,
        Semicolon,
        ForwardSlash,
        Star,
        Assign,

        //Comparisons
        Bang,
        BangEqual,
        EqualEqual,
        GreaterThan,
        GreaterThanEqual,
        LessThan,
        LessThanEqual,
        Pipe,
        Ampersand,
        DoublePipe,
        DoubleAmpersand,

        //Literals
        Ident,
        String,
        Num,
        Int,
        Float,
        Char,
        Bool,
        Void,

        //Unary
        Decrement,
        Increment,

        //Binary
        AddAssign,
        SubAssign,
        MulAssign,
        DivAssign,


        //Keywords
        If,
        Else,
        True,
        False,
        For,
        While,
        Return,
        This,
        Struct,
        Enum,
        Type,
        Pub,
        Space,
        Impl,
        Other,
        Break,
        Continue,
        Const,
        Static,
        Extern,
        Union,
        Fn,
        Class,

        EOL,

        ENDOF,
    };

    struct TokenData {
        TokenType type;

    };

    class Token {
    public:
        Token(TokenType type, std::string lexeme, uint64_t line, void* literal);
        ~Token();
    private:
        TokenType token_type;
        std::string lexeme;
        uint64_t line;
        void* literal;
    };
}


#endif //SPECTRA_TOKEN_HPP
