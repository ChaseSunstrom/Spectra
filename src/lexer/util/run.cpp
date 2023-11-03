//6
// Created by Chase on 10/31/2023.
//

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "run.hpp"
#include "../spectra.hpp"
#include "../scanner.hpp"

namespace lex {
    void run_files(const std::vector<std::filesystem::path>& files) {
        std::ifstream file;
        for (const std::filesystem::path& file_path : files) {
            std::cout << "Running file: " << file_path << std::endl;
            file.open(file_path);
            if (file.is_open()) {
                std::string line;
                std::string contents;
                while (getline(file, line)) {
                    contents += line + "\n";
                }
                file.close();
                spectra* _spectra = new spectra(false, new scanner(contents, std::vector<token>()));
                _spectra->run();
                std::cout << _spectra->get_scanner()->get_file_source() << std::endl;
                delete _spectra;
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
            spectra* _spectra = new spectra(false, new scanner(input, std::vector<token>()));
            _spectra->run();
            delete _spectra;
        }
    }
}