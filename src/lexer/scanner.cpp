//
// Created by Chase on 10/31/2023.
//

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <cctype>
#include <chrono>
#include <iostream>
#include <string.h>

#include "token.hpp"
#include "scanner.hpp"
#include "spectra.hpp"

namespace lex {
    scanner::scanner(std::string file_source, std::vector<token> tokens) {
        this->_file_source = file_source;
        this->_tokens = tokens;
        this->_keywords = this->init_keywords();
        this->_current = 0;
        this->_start = 0;
        this->_line = 1;
    }

    scanner::~scanner() {}

    std::map<std::string, token_type> scanner::init_keywords() {
        std::map<std::string, token_type> keywords;
        keywords.insert({"if", token_type::IF});
        keywords.insert({"else", token_type::ELSE});
        keywords.insert({"while", token_type::WHILE});
        keywords.insert({"for", token_type::FOR});
        keywords.insert({"return", token_type::RETURN});
        keywords.insert({"break", token_type::BREAK});
        keywords.insert({"continue", token_type::CONTINUE});
        keywords.insert({"true", token_type::TRUE});
        keywords.insert({"false", token_type::FALSE});
        keywords.insert({"void", token_type::VOID});
        keywords.insert({"int", token_type::INT});
        keywords.insert({"float", token_type::FLOAT});
        keywords.insert({"char", token_type::CHAR});
        keywords.insert({"string", token_type::STRING});
        keywords.insert({"bool", token_type::BOOL});
        keywords.insert({"none", token_type::NONE});
        keywords.insert({"this", token_type::THIS});
        keywords.insert({"struct", token_type::STRUCT});
        keywords.insert({"enum", token_type::ENUM});
        keywords.insert({"class", token_type::CLASS});
        keywords.insert({"const", token_type::CONST});
        keywords.insert({"static", token_type::STATIC});
        keywords.insert({"union", token_type::UNION});
        keywords.insert({"extern", token_type::EXTERN});
        keywords.insert({"type", token_type::TYPE});
        keywords.insert({"pub", token_type::PUB});
        keywords.insert({"priv", token_type::PRIV});
        keywords.insert({"space", token_type::SPACE});
        keywords.insert({"impl", token_type::IMPL});
        keywords.insert({"fn", token_type::FN});
        return keywords;
    }

    std::vector<token> scanner::scan() {
        while (!this->end_of_token()) {
            //using chrono for time measure
            auto start = std::chrono::high_resolution_clock::now();
            this->_start = this->_current;
            this->scan_token();
            this->_current++;
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            //this shit is fast, its 10x faster than my shitty rust code lmao
            std::cout << duration.count() << std::endl;
        }

        token _token = token(token_type::ENDOF, std::string(""), this->_line, nullptr);
        this->_tokens.emplace_back(_token);
        return this->_tokens;
    }

    void scanner::scan_token() {
        char current;
        switch (this->_current) {
            case 0:
                current = this->_file_source[this->_current];
                break;
            default:
                current = this->iterate();
                break;
        }

        switch (current) {
            case '(':
                this->add_token(token_type::LEFT_PAREN);
                break;
            case ')':
                this->add_token(token_type::RIGHT_PAREN);
                break;
            case '{':
                this->add_token(token_type::LEFT_BRACE);
                break;
            case '}':
                this->add_token(token_type::RIGHT_BRACE);
                break;
            case ',':
                this->add_token(token_type::COMMA);
                break;
            case '.':
                this->add_token(token_type::DOT);
                break;
            case ';':
                this->add_token(token_type::SEMICOLON);
                break;
            case '+':
                if (this->check('=')) {
                    this->add_token(token_type::ADD_ASSIGN);
                } else if (this->check('+')) {
                    this->add_token(token_type::INCREMENT);
                } else {
                    this->add_token(token_type::PLUS);
                }
                break;
            case '*':
                if (this->check('=')) {
                    this->add_token(token_type::MUL_ASSIGN);
                } else {
                    this->add_token(token_type::STAR);
                }
                break;
            case '-':
                if (this->check('=')) {
                    this->add_token(token_type::SUB_ASSIGN);
                } else if (this->check('-')) {
                    this->add_token(token_type::DECREMENT);
                } else {
                    this->add_token(token_type::TACK);
                }
                break;
            case '"':
                this->string();
                break;
            case '\n':
                this->add_token(token_type::EOL);
                _line++;
                break;
            case '\t':
            case '\r':
                break;
            case ' ':
                this->_file_source.insert(this->_current, " ");
                break;
            case '/':
                if (this->check('/')) {
                    while (this->peek() != '\n' && !this->end_of_token()) {
                        this->iterate();
                    }
                } else if (this->check('=')) {
                    this->add_token(token_type::DIV_ASSIGN);
                } else {
                    this->add_token(token_type::SLASH);
                }
                break;
            case '!':
                if (this->check('=')) {
                    this->add_token(token_type::BANG_EQUAL);
                } else {
                    this->add_token(token_type::BANG);
                }
                break;
            case '=':
                if (this->check('=')) {
                    this->add_token(token_type::EQUAL);
                } else {
                    this->add_token(token_type::ASSIGN);
                }
                break;
            case '>':
                if (this->check('=')) {
                    this->add_token(token_type::GREATER_THAN_EQUAL);
                } else {
                    this->add_token(token_type::GREATER_THAN);
                }
                break;
            case '<':
                if (this->check('=')) {
                    this->add_token(token_type::LESS_THAN_EQUAL);
                } else {
                    this->add_token(token_type::LESS_THAN);
                }
                break;
            case '&':
                if (this->check('&')) {
                    this->add_token(token_type::DOUBLE_AMPERSAND);
                } else {
                    this->add_token(token_type::AMPERSAND);
                }
                break;
            case '|':
                if (this->check('|')) {
                    this->add_token(token_type::DOUBLE_PIPE);
                } else {
                    this->add_token(token_type::PIPE);
                }
                break;
            default:
                if (this->is_num(current)) {
                    this->number();
                } else if (this->is_alpha(current)) {
                    this->identifier();
                } else {
                    spectra::error(_line, "Unexpected character.");
                }
                break;
        }

    }

    void scanner::add_token(token_type type) {
        this->add_token(type, nullptr);
    }

    void scanner::add_token(token_type type, token_data *literal) {
        this->_tokens.emplace_back(type, this->_file_source.substr(this->_start, this->_current + 1), this->_line, literal);
        this->_file_source.insert(this->_current + 1, " ");
    }

    char scanner::iterate() {
        this->_current++;
        return this->_file_source[this->_current];
    }

    char scanner::peek() {
        return this->_file_source[this->_current];
    }

    char scanner::peek_next() {
        return this->_file_source[this->_current];
    }

    bool scanner::end_of_token() {
        return this->_current >= this->_file_source.size();
    }

    bool scanner::is_num(char c) {
        return c >= '0' && c <= '9';
    }

    bool scanner::is_alpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool scanner::is_alpha_or_num(char c) {
        return this->is_alpha(c) || this->is_num(c);
    }

    bool scanner::check(char expected) {
        if (this->end_of_token()) {
            return false;
        }
        if (this->_file_source[this->_current + 1] != expected) {
            return false;
        }
        this->_current++;
        return true;
    }

    //very unsafe lmao
    void scanner::identifier() {
        while (this->is_alpha_or_num(this->peek())) {
            if (this->peek() == ' ') {
                break;
            }
            this->iterate();
        }
        this->_file_source.insert(this->_current, " ");
        std::string source = this->_file_source.substr(this->_start, this->_current);
        char* tok = strtok(source.data(), " ");
        token_type type;
        if (this->_keywords.find(tok) == this->_keywords.end()) {
            type = token_type::IDENT;
        } else {
            type = this->_keywords[tok];
        }

        this->add_token(type);
    }

    void scanner::string() {
        std::string value;
        if (this->peek() == '"') {
            this->iterate(); // Skip the opening quote
            while (this->peek() != '"' && !this->end_of_token()) {
                if (this->peek() == '\n') {
                    this->_line++;
                }
                value += this->peek();
                this->iterate();
            }
        }

        if (this->end_of_token()) {
            spectra::error(this->_line, "Unterminated string.");
            return;
        }

        this->iterate();

        this->_file_source.insert(this->_current, " ");
        this->add_token(token_type::STRING, new token_data(value_type::STRING, value));
    }

    void scanner::number() {
        while (this->is_num(this->peek())) {
            this->iterate();
        }
        if (this->peek() == '.' || this->is_num(this->peek_next())) {
            this->iterate();
            while (this->is_num(this->peek())) {
                this->iterate();
            }
        }

        std::string num = this->_file_source.substr(this->_start, this->_current);
        value_type num_type;

        if (num.find('.') != std::string::npos) {
            num_type = value_type::FLOAT;
            float num_float = std::stof(num);
            token_data *float_data = new token_data(num_type, num_float);
            this->add_token(token::convert_value_to_type(num_type), float_data);
        } else {
            num_type = value_type::INT;
            int num_int = std::stoi(num);
            token_data *int_data = new token_data(num_type, num_int);
            this->add_token(token::convert_value_to_type(num_type), int_data);
        }
    }

    std::string scanner::get_file_source() {
        return this->_file_source;
    }
}