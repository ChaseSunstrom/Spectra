//
// Created by Chase on 11/13/2023.
//

#ifndef SPECTRA_UNIT_TESTS_HPP
#define SPECTRA_UNIT_TESTS_HPP

namespace tests {
    void test_main();
    void test_expression_accept();
    void test_expression_binary_expression();
    void test_expression_unary_expression();
    void test_expression_literal();
    void test_expression_grouping();
    void test_scanner_scan();
    void test_scanner_string();
    void test_scanner_identifier();
    void test_spectra_error();
    void test_spectra_runtime_error();
    void test_token_token_data();
    void test_parser_expression();
    void test_parser_equality();
    void test_parser_comparison();
    void test_parser_term();
    void test_parser_factor();
    void test_parser_unary();
    void test_parser_primary();
    void test_parser_match();
    void test_parser_check();
    void test_interpreter_visit_literal_expression();
    void test_interpreter_visit_grouping_expression();
    void test_interpreter_visit_unary_expression();
    void test_interpreter_visit_binary_expression();
    void test_interpreter_evaluate_expression();
    void test_interpreter_make_string();
} // tests

#endif //SPECTRA_UNIT_TESTS_HPP
