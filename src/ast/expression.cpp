//
// Created by Chase on 11/3/2023.
//
#include <vector>
#include <string>

#include "expression.hpp"
#include "../util/debug.hpp"

namespace ast {
    binary_expression::binary_expression(std::shared_ptr<expression> left, std::shared_ptr<lex::token> operator_,
                                         std::shared_ptr<expression> right) {
        this->_left = std::move(left);
        this->_operator = std::move(operator_);
        this->_right = std::move(right);
    }

    std::string binary_expression::accept() {
        return this->visit_binary_expression();
    }

    std::string binary_expression::visit_binary_expression() {
        return parenthesize(this->_operator->get_lexeme(), std::vector<std::shared_ptr<expression>>{
                std::move(this->_left),
                std::move(this->_right)});
    }

    unary_expression::unary_expression(std::shared_ptr<lex::token> operator_, std::shared_ptr<expression> right) {
        this->_operator = std::move(operator_);
        this->_right = std::move(right);
    }

    std::string unary_expression::accept() {
        return this->visit_unary_expression();
    }

    std::string unary_expression::visit_unary_expression() {
        return parenthesize(this->_operator->get_lexeme(), std::vector<std::shared_ptr<expression>>{
                std::move(this->_right)
        });
    }

    grouping_expression::grouping_expression(std::shared_ptr<expression> expression) {
        this->_expression = std::move(expression);
    }

    std::string grouping_expression::accept() {
        return this->visit_grouping_expression();
    }

    std::string grouping_expression::visit_grouping_expression() {
        return parenthesize("grouping", std::vector<std::shared_ptr<expression>>{
                std::move(this->_expression)
        });
    }

    template <typename T>
    std::string literal_expression<T>::accept() {
        return this->visit_literal_expression();
    }

    template <typename T>
    std::string literal_expression<T>::visit_literal_expression() {
        if (!this->_value) {
            return "none";
        }
        return std::to_string(this->_value);
    }

    std::string parenthesize(const std::string& name, const std::vector<std::shared_ptr<expression>>& expressions) {
        std::string output = "(" + name + " ";
        for (auto &expression : expressions) {
            output += " ";
            output += expression->accept();
        }
        output += " )";
        return output;
    }

    void print_expression(expression* expression) {
        std::cout << expression->accept() << std::endl;
    }
} // ast