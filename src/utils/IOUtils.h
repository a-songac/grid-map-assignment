/// @file
/// @brief Header file containing method declarations for useful IO operations
/// @details  No specific game rule enforced by the class.
/// Provides method that encapsulate command line user input validation
/// No specific library is used.

#pragma once

#include <iostream>

using namespace std;

bool readYesNoInput(string prompt, bool defaultAns);
string readStringInput(string prompt, string defaultAns);
int readIntegerInput(string prompt, int defaultAns);
double readDoubleInput(string prompt, double defaultAns);
