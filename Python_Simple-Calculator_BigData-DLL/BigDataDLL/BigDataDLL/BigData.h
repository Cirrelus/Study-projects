// BigData.h - Contains declarations of math functions for big data
#pragma once
#include <string>
#include <cstring>

#ifdef BIGDATA_EXPORTS
#define BIGDATA_API __declspec(dllexport)
#else
#define BIGDATA_API __declspec(dllimport)
#endif

// Big data are too large to be contained in a single variable. 
// This DLL does basic arithmetic on strings that contains big numbers 

// remove zeros from the start
std::string EraseZeros(std::string line);

// Calculate a sum of two numbers 
// Wrapper of operator for dll
extern "C" BIGDATA_API char* Plus(char* arg1, char* arg2);
// A version for Multiply, Divide and testing
std::string Plus(std::string left_side, std::string right_side);
// A function that sums
std::string operator+ (std::string arg1, std::string arg2);

// Calculate a subtruction of two numbers
// Wrapper of operator for dll
extern "C" BIGDATA_API char* Minus(char* arg1, char* arg2);
// A version for Multiply, Divide and testing
std::string Minus(std::string left_side, std::string right_side);
// A function that substracs
std::string operator- (std::string arg1, std::string arg2);

// Calculate a multiplication of two numbers
extern "C" BIGDATA_API char* Multiply(char* arg1, char* arg2);
// A version for testing
std::string Multiply(std::string left_side, std::string right_side);

// Calculate a division of two numbers
extern "C" BIGDATA_API char* Divide(char* arg1, char* arg2);
// A version for testing
std::string Divide(std::string left_side, std::string right_side);