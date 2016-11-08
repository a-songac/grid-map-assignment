/// @file
/// @brief Header file containing method declarations for useful IO operations
/// @details  1. Game Rules: No specific game rule enforced by the class. \n\n
/// 2. Design: Provides method that encapsulate command line user input validation \n\n
/// 3. Libraries: Uses the string std library to perform conversion from string to numbers
#pragma once

#include <iostream>

using namespace std;

bool readYesNoInput(string prompt, bool defaultAns);
string readStringInput(string prompt, string defaultAns);
string readFileName(string prompt);
int readIntegerInput(string prompt, int defaultAns);
int readIntegerInputWithRange(string prompt, int defaultAns, int minimum, int maximum);
double readDoubleInput(string prompt, double defaultAns);
