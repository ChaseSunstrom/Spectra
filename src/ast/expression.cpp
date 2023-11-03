//
// Created by Chase on 11/3/2023.
//

#include "expression.hpp"

namespace ast {
    binary_expression::binary_expression(std::unique_ptr<expression> left, std::unique_ptr<lex::token> operator_,
                                         std::unique_ptr<expression> right) {
        this->_left = std::move(left);
        this->_operator = std::move(operator_);
        this->_right = std::move(right);
    }

    template <typename T>
    T binary_expression::accept(visitor<T> ) {
        return this->visit_binary_expression<T>();
    }
} // ast