//
// Created by Chase on 10/31/2023.
//

#include<vector>
#include <string>
#include<iostream>
#include <fstream>

#include "run.hpp"

namespace lex {
    void run_files(const std::vector<std::string>& files) {
        std::ifstream file;
        for (const std::string& file_path : files) {
            std::cout << file_path << std::endl;
            file.open(file_path);
            if (file.is_open()) {
                std::string line;
                std::string contents;
                while (getline(file, line)) {
                    contents += line;
                }
                file.close();
            }
        }
    }

    void run_prompt() {
        std::string input;

        while (true) {
            std::cout << "> ";
            std::getline(std::cin, input);

            if (input.empty()) {
                break;
            }


        }
    }

}