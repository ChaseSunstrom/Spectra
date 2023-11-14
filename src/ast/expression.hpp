//
// Created by Chase on 11/3/2023.
//

#ifndef SPECTRA_EXPRESSION_HPP
#define SPECTRA_EXPRESSION_HPP

#include <memory>
#include <vector>
#include <string>
#include <cstring>

#include "../lexer/token.hpp"

namespace ast {
    class expression {
    public:
        expression() = default;

        ~expression() = default;

        virtual std::string accept() = 0;
    };

    class binary_expression : public expression {
    public:
        binary_expression(std::shared_ptr<expression> left, std::shared_ptr<lex::token> operator_,
                          std::shared_ptr<expression> right);

        std::string accept();

        std::string visit_binary_expression();

        inline std::shared_ptr<expression> get_left() { return _left; }

        inline std::shared_ptr<expression> get_right() { return _right; }

        inline std::shared_ptr<lex::token> get_operator() { return _operator; }

    private:
        std::shared_ptr<expression> _left;
        std::shared_ptr<expression> _right;
        std::shared_ptr<lex::token> _operator;
    };

    class unary_expression : public expression {
    public:
        unary_expression(std::shared_ptr<lex::token> operator_, std::shared_ptr<expression> right);

        std::string accept();

        std::string visit_unary_expression();

        std::shared_ptr<expression> get_right();

        std::shared_ptr<lex::token> get_operator();

    private:
        std::shared_ptr<expression> _right;
        std::shared_ptr<lex::token> _operator;
    };

    class grouping_expression : public expression {
    public:
        explicit grouping_expression(std::shared_ptr<expression> expression);

        std::string accept();

        std::string visit_grouping_expression();

        inline std::shared_ptr<expression> get_expression() { return _expression; }

    private:
        std::shared_ptr<expression> _expression;
    };

    template<typename T>
    class literal_expression : public expression {
    public:
        explicit literal_expression(T *value) : _value(value) {};

        std::string accept() { return this->visit_literal_expression(); }

        std::string visit_literal_expression() {
            if (strcmp(typeid(_value).name(), "token_data") && this->_value)
                return this->visit_literal_expression_impl((lex::token_data *) _value);
            else if (this->_value == nullptr)
                return "none";
            else
                return visit_literal_expression_impl();
        }

        inline T *get_value() { return _value; }

    private:
        std::string visit_literal_expression_impl() {
            return typeid(this->_value).name();
        };

        inline std::string
        visit_literal_expression_impl(lex::token_data *data) { return data->convert_value_to_string(); }

    private:
        T *_value;
    };

    std::string parenthesize(const std::string &name, const std::vector<std::shared_ptr<expression>> &expressions);
}  // namespace ast

#endif  // SPECTRA_EXPRESSION_HPP
