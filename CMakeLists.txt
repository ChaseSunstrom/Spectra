cmake_minimum_required(VERSION 3.26)
project(Spectra)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DARGV="${ARGV}")

add_executable(Spectra src/main.cpp
        src/lexer/util/run.cpp
        src/lexer/util/run.hpp
        src/lexer/scanner.cpp
        src/lexer/scanner.hpp
        src/lexer/spectra.cpp
        src/lexer/spectra.hpp
        src/lexer/token.cpp
        src/lexer/token.hpp)
