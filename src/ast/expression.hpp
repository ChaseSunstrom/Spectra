//
// Created by Chase on 11/3/2023.
//

#ifndef SPECTRA_EXPRESSION_HPP
#define SPECTRA_EXPRESSION_HPP

#include <memory>

#include "../lexer/token.hpp"

namespace ast {
class expression {
   public:
    template <typename T>
    T accept();
};

class binary_expression : public expression {
   public:
    binary_expression(std::unique_ptr<expression> left, std::unique_ptr<lex::token> operator_, std::unique_ptr<expression> right);
    template <typename T>
    T accept();
    template <typename T>
    T visit_binary_expression();

   private:
    std::unique_ptr<expression> _left;
    std::unique_ptr<expression> _right;
    std::unique_ptr<lex::token> _operator;
};

class unary_expression : public expression {
   public:
    unary_expression(lex::token operator_, std::unique_ptr<expression> right);
    template <typename T>
    T accept();
    template <typename T>
    T visit_unary_expression();

   private:
    std::unique_ptr<expression> _right;
    lex::token _operator;
};

class grouping_expression : public expression {
   public:
    grouping_expression(std::unique_ptr<expression> expression);
    template <typename T>
    T accept();
    template <typename T>
    T visit_grouping_expression();

   private:
    std::unique_ptr<expression> _expression;
};

template <typename T>
class literal_expression : public expression {
   public:
    literal_expression(T value);
    T accept();
    T visit_literal_expression();

   private:
    T _value;
};

void parenthesize(std::unique_ptr<expression> expression);
}  // namespace ast

#endif  // SPECTRA_EXPRESSION_HPP
