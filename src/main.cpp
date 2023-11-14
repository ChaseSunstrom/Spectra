#include <filesystem>

#include "lexer/util/run.hpp"
#include "tests/unit_tests.hpp"

void language_main(int argc, char *argv[]) {
    if (argc == 1) {
        lex::run_prompt();
    } else {
        std::vector<std::filesystem::path> files;

        for (int i = 1; i < argc; i++) {
            std::filesystem::path file_path = std::filesystem::path(argv[i]);
            files.emplace_back(file_path);
        }

        lex::run_files(files);
    }
}


int main(int argc, char *argv[]) {
//#define DEBUG
#ifndef DEBUG
    language_main(argc, argv);
#else
    tests::test_main();
#endif
}

