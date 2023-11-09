//
// Created by Chase on 11/9/2023.
//

#ifndef SPECTRA_INTERPRETER_HPP
#define SPECTRA_INTERPRETER_HPP

#include <stdexcept>

#include "../lexer/token.hpp"
#include "../ast/expression.hpp"
#include "../util/debug.hpp"
#include "../lexer/spectra.hpp"

namespace ev {
    class runtime_error : public std::runtime_error {
        std::string _message;
        lex::token _token;
    public:
        explicit runtime_error(lex::token token, std::string message) : std::runtime_error(message),
                                                                        _message(message), _token(token) {
            REPORT_ERROR(token.get_line(), message)
        }

        inline lex::token get_token()  {
            return _token;
        }

        inline std::string get_message() {
            return _message;
        }

        const char *what() const noexcept override {
            return _message.c_str();
        }
    };
    class interpreter {
    public:

        interpreter() = default;

        template<typename T>
        T visit_literal_expression(ast::literal_expression<T> *expr);

        template<typename T>
        T visit_unary_expression(ast::unary_expression *expr);

        template<typename T>
        T visit_binary_expression(ast::binary_expression *expr);

        template<typename T>
        T visit_grouping_expression(ast::grouping_expression *expr);

        template <typename T>
        void interpret(ast::expression* expr) {
            try {
                T value = this->evaluate_expression<ast::expression>(expr);
                std::cout << make_string<typeof(T)>(&value) << std::endl;
            } catch (runtime_error e) {
                lex::spectra::runtime_error();
            }
        }
    private:
        template<typename T>
        T evaluate_expression(ast::expression *expr);

        template<typename T>
        bool is_true(T *value);

        template<typename T>
        bool is_equal(T *left, T *right);

        template<typename T>
        void check_number_operand(lex::token* op, T* operand);

        template <typename T>
        void check_number_operands(lex::token* op, T* left, T* right);

        template <typename T>
        std::string make_string(T *value);
    };
} // ev

#endif //SPECTRA_INTERPRETER_HPP
