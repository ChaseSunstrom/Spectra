//
// Created by Chase on 11/6/2023.
//

#include <memory>
#include <stdexcept>

#include "parser.hpp"


namespace parse {

    parser::parser(std::vector<lex::token> tokens) {
        this->_tokens = std::move(tokens);
        this->_current = 0;
    }

    ast::expression* parser::expression() {
        // ! Hear int is being parsed as equality something like x=1 won't segfault
        return this->equality();
    }

    ast::expression* parser::equality() {

       ast::expression* expression = this->comparison();

        while (this->match(std::vector<lex::token_type>{lex::token_type::BANG_EQUAL, lex::token_type::EQUAL})) {
             expression = new ast::binary_expression(
                    std::shared_ptr<ast::expression>(this->comparison()),
                    std::make_shared<lex::token>(this->previous()),
                    std::shared_ptr<ast::expression>(this->comparison()));
            DEBUG_PRINT(&*expression)
        }

        return expression;
    }

    bool parser::match(const std::vector<lex::token_type> &types) {
        for (lex::token_type type: types) {
            if (this->check(type)) {
                this->advance();
                return true;
            }
        }
        return false;
    }

    bool parser::check(const lex::token_type &type) {
        if (this->end_of_file()) {
            return false;
        }
        return this->peek().get_type() == type;
    }

    lex::token parser::advance() {
        if (!this->end_of_file()) {
            this->_current++;
        }
        return this->previous();
    }

    bool parser::end_of_file() {
        return this->peek().get_type() == lex::token_type::ENDOF;
    }

    lex::token parser::peek() {
        return this->_tokens.at(this->_current);
    }

    lex::token parser::previous() {
        return this->_tokens.at(this->_current - 1);
    }

    ast::expression *parser::comparison() {
        ast::expression *expression = this->term();
        while (this->match(std::vector<lex::token_type>{
                lex::token_type::GREATER_THAN,
                lex::token_type::GREATER_THAN_EQUAL,
                lex::token_type::LESS_THAN,
                lex::token_type::LESS_THAN_EQUAL})) {
            expression = new ast::binary_expression(
                    std::shared_ptr<ast::expression>(this->term()),
                    std::make_shared<lex::token>(this->previous()),
                    std::shared_ptr<ast::expression>(this->term()));
        }

        return expression;
    }

    ast::expression *parser::term() {
        ast::expression *expression = this->factor();
        while (this->match(std::vector<lex::token_type>{lex::token_type::TACK, lex::token_type::PLUS})) {
            expression = new ast::binary_expression(
                    std::shared_ptr<ast::expression>(this->factor()),
                    std::make_shared<lex::token>(this->previous()),
                    std::shared_ptr<ast::expression>(this->factor()));
        }
        return expression;
    }

    ast::expression *parser::factor() {
        ast::expression *expression = this->unary();
        while (this->match(std::vector<lex::token_type>{lex::token_type::SLASH, lex::token_type::STAR})) {
            expression = new ast::binary_expression(
                    std::shared_ptr<ast::expression>(this->unary()),
                    std::make_shared<lex::token>(this->previous()),
                    std::shared_ptr<ast::expression>(this->unary()));
        }
        return expression;
    }

    ast::expression *parser::unary() {
        if (this->match(std::vector<lex::token_type>{lex::token_type::BANG, lex::token_type::TACK})) {
            return new ast::unary_expression(
                    std::make_shared<lex::token>(this->previous()),
                    std::unique_ptr<ast::expression>(this->unary()));
        }
        return this->primary();
    }

    ast::expression *parser::primary() {
        if (this->match(std::vector<lex::token_type>{lex::token_type::INT, lex::token_type::FLOAT})) {
            return new ast::literal_expression<lex::token_data>(this->previous().get_literal());
        }
        if (this->match(std::vector<lex::token_type>{lex::token_type::FALSE})) {
            bool _false = false;
            return new ast::literal_expression<bool>(&_false);
        }
        if (this->match(std::vector<lex::token_type>{lex::token_type::TRUE})) {
            bool _true = true;
            return new ast::literal_expression<bool>(&_true);
        }
        if (this->match(std::vector<lex::token_type>{lex::token_type::NONE})) {
            return new ast::literal_expression<std::nullptr_t>(nullptr);
        }
        if (this->match(std::vector<lex::token_type>{lex::token_type::LEFT_PAREN})) {
            ast::expression *expression = this->expression();
            this->consume(lex::token_type::RIGHT_PAREN, "Expected ')'");
            return new ast::grouping_expression(std::unique_ptr<ast::expression>(expression));
        }

        throw parse_error(this->peek(), "Expected expression.");
    }

    lex::token parser::consume(lex::token_type type, std::string message) {
        if (this->check(type)) {
            return this->advance();
        }
        throw parse_error(this->peek(), message);
    }

    void parser::synchronize() {
        this->advance();

        while (!this->end_of_file()) {
            if (this->previous().get_type() == lex::token_type::SEMICOLON) {
                return;
            }
            switch (this->peek().get_type()) {
                case lex::token_type::CLASS:
                case lex::token_type::STRUCT:
                case lex::token_type::UNION:
                case lex::token_type::ENUM:
                case lex::token_type::FN:
                case lex::token_type::IF:
                case lex::token_type::FOR:
                case lex::token_type::WHILE:
                case lex::token_type::RETURN:
                    return;
            }
            this->advance();
        }
    }

    ast::expression* parser::parse() {
        try {
            return this->expression();
        } catch (parse_error &error) {
            return nullptr;
        }
    }
} // parse