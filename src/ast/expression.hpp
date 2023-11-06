//
// Created by Chase on 11/3/2023.
//

#ifndef SPECTRA_EXPRESSION_HPP
#define SPECTRA_EXPRESSION_HPP

#include <memory>
#include <vector>
#include <string>

#include "../lexer/token.hpp"

namespace ast {
    class expression {
    public:
        expression() = default;
        virtual std::string accept() = 0;
    };

    class binary_expression : public expression {
    public:
        binary_expression(std::shared_ptr<expression> left, std::shared_ptr<lex::token> operator_,
                          std::shared_ptr<expression> right);

        std::string accept() override;

        std::string visit_binary_expression();

    private:
        std::shared_ptr<expression> _left;
        std::shared_ptr<expression> _right;
        std::shared_ptr<lex::token> _operator;
    };

    class unary_expression : public expression {
    public:
        unary_expression(std::shared_ptr<lex::token> operator_, std::shared_ptr<expression> right);

        std::string accept() override;

        std::string visit_unary_expression();

    private:
        std::shared_ptr<expression> _right;
        std::shared_ptr<lex::token> _operator;
    };

    class grouping_expression : public expression {
    public:
        explicit grouping_expression(std::shared_ptr<expression> expression);

        std::string accept() override;

        std::string visit_grouping_expression();

    private:
        std::shared_ptr<expression> _expression;
    };

    template<typename T>
    class literal_expression : public expression {
    public:
        explicit literal_expression(T *value) : _value(value) {};

        std::string accept() override;

        std::string visit_literal_expression();

    private:
        T *_value;
    };

    std::string parenthesize(const std::string &name, const std::vector<std::shared_ptr<expression>>& expressions);

    void print_expression(expression *expression);


}  // namespace ast

#endif  // SPECTRA_EXPRESSION_HPP
