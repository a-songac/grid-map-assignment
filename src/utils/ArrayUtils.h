/// @file
/// @brief Header file containing method declarations for useful 2D array manipulations
/// @details  1. Game Rules: No specific game rule enforced by the class. \n\n
/// 2. Design: Helper class for 2D array initialization and destruction. \n\n
/// 3. No specific library is used.


#pragma once

void initialize2DArray(bool** grid, int height, int width);
void initialize2DArray(int** grid, int height, int width);
void reset2DArray(bool** grid, int height, int width);
void reset2DArray(int** grid, int height, int width);
void destroy2DArray(bool** grid, int height, int width);
void destroy2DArray(int** grid, int height, int width);
