cmake_minimum_required(VERSION 3.26)
project(Spectra)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DARGV="${ARGV}")

#dont add header files to this if they have a corresponding source file, the linker will do that automatically
add_executable(Spectra src/main.cpp
        src/lexer/util/run.cpp
        src/lexer/scanner.cpp
        src/lexer/spectra.cpp
        src/lexer/token.cpp
        src/util/debug.hpp
        src/ast/expression.cpp
        src/parser/parser.cpp
        src/parser/parser.hpp
)
