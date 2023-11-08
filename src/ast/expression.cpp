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
        DEBUG_PRINT("Visiting binary expression");

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
        DEBUG_PRINT("Visiting unary expression");
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
        DEBUG_PRINT("Visiting grouping expression");
        return this->visit_grouping_expression();
    }

    std::string grouping_expression::visit_grouping_expression() {
        return parenthesize("grouping", std::vector<std::shared_ptr<expression>>{
                std::move(this->_expression)
        });
    }

    std::string parenthesize(const std::string& name, const std::vector<std::shared_ptr<expression>>& expressions) {
        std::string output = "(" + name + " ";
        for (const auto& expression : expressions) {
            output += " ";
            output += expression->accept();
        }
        output += " )";
        return output;
    }
} // ast