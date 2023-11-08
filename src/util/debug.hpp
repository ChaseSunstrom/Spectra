//
// Created by Chase on 11/3/2023.
//

#ifndef SPECTRA_DEBUG_HPP
#define SPECTRA_DEBUG_HPP

#define REPORT_ERROR(line, message)                                       \
    std::cout << "[LINE " << line << "] Error: " << message << std::endl; \
    

#define DEBUG
#ifdef DEBUG

#include <chrono>
#include <iostream>

#define DEBUG_PRINT(x) std::cout << x << std::endl;

#define FUNCTION_TIME_START() std::chrono::high_resolution_clock::now();
#define FUNCTION_TIME_END() std::chrono::high_resolution_clock::now();
#define PRINT_FUNCTION_TIME(start, stop) DEBUG_PRINT(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

#else

#define DEBUG_PRINT(x)

// DO NOT USE THESE VARIABLES ANYWHERE BUT IN MACRO CALLS RELATED TO THEM
#define FUNCTION_TIME_START() nullptr
#define FUNCTION_TIME_END() nullptr
#define PRINT_FUNCTION_TIME(start, stop)

#endif
#endif  // SPECTRA_DEBUG_HPP