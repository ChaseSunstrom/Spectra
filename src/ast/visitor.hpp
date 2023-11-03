//
// Created by Chase on 11/3/2023.
//

#ifndef SPECTRA_VISITOR_HPP
#define SPECTRA_VISITOR_HPP

#include "expression.hpp"

namespace ast {
    template <typename T>
    class visitor {
    public:
        virtual T visit_binary_expr(binary_expression expr) = 0;
        virtual T visit_unary_expr(unary_expression expr) = 0;
        virtual T visit_literal_expr(literal_expression<T> expr) = 0;
        virtual T visit_grouping_expr(grouping_expression expr) = 0;
    };

} // ast

#endif //SPECTRA_VISITOR_HPP
