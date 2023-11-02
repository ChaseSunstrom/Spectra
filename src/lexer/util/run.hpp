//
// Created by Chase on 10/31/2023.
//

#ifndef SPECTRA_RUN_HPP
#define SPECTRA_RUN_HPP

#include <vector>
#include <string>
#include <filesystem>

namespace lex {
    void run_files(const std::vector<std::filesystem::path>& files);
    void run_prompt();
    void run();
}

#endif //SPECTRA_RUN_HPP