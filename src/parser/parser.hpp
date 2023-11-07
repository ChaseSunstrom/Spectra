//
// Created by Chase on 11/6/2023.
//

#ifndef SPECTRA_PARSER_HPP
#define SPECTRA_PARSER_HPP

#include <vector>
#include <string>
#include <stdexcept>

#include "../ast/expression.hpp"
#include "../lexer/token.hpp"
#include "../util/debug.hpp"

namespace parse {
    class parse_error : public std::runtime_error {
        std::string _message;
    public:
        explicit parse_error(lex::token token, std::string message) : runtime_error(message),
                                                                         _message(std::move(message)) {
                                                                            REPORT_ERROR(token.get_line(), message)
                                                                         }
        const char *what() const noexcept override {
            return _message.c_str();
        }
    };
    class parser {
    public:
        explicit parser(std::vector<lex::token> tokens);

        ast::expression* parse();

    private:
        ast::expression* expression();
        ast::expression* equality();
        ast::expression* comparison();
        ast::expression* term();
        ast::expression* factor();
        ast::expression* unary();
        ast::expression* primary();
        bool match(const std::vector<lex::token_type> &types);
        bool check(const lex::token_type &type);
        bool end_of_file();
        lex::token peek();
        lex::token previous();
        lex::token advance();
        lex::token consume(lex::token_type type, std::string message);
        void syncronize();
        parse_error error(lex::token token, std::string message);
    private:
        std::vector<lex::token> _tokens;
        int _current;
    };
} // parse

#endif //SPECTRA_PARSER_HPP
