//
// Created by Chase on 11/9/2023.
//
#include <cstring>


#include "../lexer/spectra.hpp"
#include "interpreter.hpp"
#include "../ast/expression.hpp"

namespace inter {
    template<typename T>
    T interpreter::visit_literal_expression(ast::literal_expression<T> *expr) {
        return expr->get_value();
    }

    template<typename T>
    T interpreter::visit_unary_expression(ast::unary_expression *expr) {
        T right = this->evaluate_expression(&*expr->get_right());
        switch (expr->get_operator()->get_type()) {
            case lex::token_type::TACK:
                this->check_number_operand(expr->get_operator(), &right);
                return -(double)right;
            case lex::token_type::BANG:
                return !is_true<ast::expression>(&right);
        }
        return nullptr;
    }

    template<typename T>
    T interpreter::visit_binary_expression(ast::binary_expression *expr) {
        T left = this->evaluate_expression(&*expr->get_left());
        T right = this->evaluate_expression(&*expr->get_right());

        switch (expr->get_operator()->get_type()) {
            case lex::token_type::GREATER_THAN:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return (double) left > (double) right;
            case lex::token_type::LESS_THAN:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return (double) left < (double) right;
            case lex::token_type::GREATER_THAN_EQUAL:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return (double) left >= (double) right;
            case lex::token_type::LESS_THAN_EQUAL:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return (double) left <= (double) right;
            case lex::token_type::BANG_EQUAL:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return !is_equal<ast::expression>(&left, &right);
            case lex::token_type::EQUAL:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return is_equal<ast::expression>(&left, &right);
            case lex::token_type::PLUS:
                if (strcmp(typeid(*left).name(), "double") && strcmp(typeid(*right).name(), "double")) {
                    return (double) left + (double) right;
                }
                if (strcmp(typeid(*left).name(), "int") && strcmp(typeid(*right).name(), "int")) {
                    return (int) left + (int) right;
                }
                if (strcmp(typeid(*left).name(), "string") && strcmp(typeid(*right).name(), "string")) {
                    return (std::string) left + (std::string) right;
                }
                throw new runtime_error(*expr->get_operator(), "Operands must be similar types.");
            case lex::token_type::TACK:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return (double) left - (double) right;
            case lex::token_type::SLASH:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return (double) left / (double) right;
            case lex::token_type::STAR:
                this->check_number_operands(expr->get_operator(), &left, &right);
                return (double) left * (double) right;
        }

        return nullptr;
    }

    template<typename T>
    T interpreter::visit_grouping_expression(ast::grouping_expression *expr) {
        return this->evaluate_expression(&*expr->get_expression());
    }

     std::string interpreter::evaluate_expression(ast::expression* expr) {
        return expr->accept();
    }

    template<typename T>
    bool interpreter::is_true(T *value) {
        if (value == nullptr) {
            return false;
        }
        if (strcmp(typeid(*value).name(), "bool")) {
            return (bool) *value;
        }
        return true;
    }

    template<typename T>
    bool interpreter::is_equal(T *left, T *right) {
        if (*left == nullptr && *right == nullptr) {
            return true;
        }
        if (*left == nullptr || *right == nullptr) {
            return false;
        }

        return *left == *right;
    }

    template <typename T>
    void interpreter::check_number_operand(lex::token* op, T* operand) {
        if (strcmp(typeid(*operand).name(), "double")||
        strcmp(typeid(*operand).name(), "int")) {
            return;
        }
        throw new runtime_error(*op, "Operand must be a number.");
    }

    template <typename T>
    void interpreter::check_number_operands(lex::token* op, T* left, T* right) {
        if ((strcmp(typeid(*left).name(), "double") ||
             strcmp(typeid(*left).name(), "int")) &&
            (strcmp(typeid(*right).name(), "double")||
             strcmp(typeid(*right).name(), "int"))) {
            return;
        }
        throw runtime_error(*op, "Operands must be numbers.");
    }


} // inter