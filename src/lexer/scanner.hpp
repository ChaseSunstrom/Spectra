//
// Created by Chase on 10/31/2023.
//

#ifndef SPECTRA_SCANNER_HPP
#define SPECTRA_SCANNER_HPP

#include <string>
#include <vector>
#include <map>

#include "token.hpp"

namespace lex {
    class scanner {
    public:
        scanner(std::string file_source, std::vector<token> tokens);
        ~scanner();
        void add_token(token_type type);
        void add_token(token_type type, token_data *literal);
        void scan_token();
        void identifier();
        void string();
        void number();
        void custom();
        void boolean();
        bool is_alpha_or_num(char c);
        bool is_alpha(char c);
        bool is_custom(char c);
        bool is_bool(char c);
        bool check(char expected);
        bool is_num(char c);
        bool end_of_token();
        char peek();
        char peek_next();
        char iterate();
        std::vector<token> scan();
        std::map<std::string, token_type> init_keywords();
        std::string get_file_source();
    private:
        std::string _file_source;
        std::vector<token> _tokens;
        std::map<std::string, token_type> _keywords;
        uint64_t _current;
        uint64_t _line;
        uint64_t _start;
    };
}
#endif //SPECTRA_SCANNER_HPP