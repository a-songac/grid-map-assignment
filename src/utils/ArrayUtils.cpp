#include "ArrayUtils.h"

void initialize2DArray(bool** grid, int height, int width) {
    for(int i = 0; i < height; ++i) {
        grid[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            grid[i][j] = false;
        }
    }
}
void initialize2DArray(int** grid, int height, int width) {
    for(int i = 0; i < height; ++i) {
        grid[i] = new int[width];
        for (int j = 0; j < width; j++) {
            grid[i][j] = 0;
        }
    }
}

void reset2DArray(bool** grid, int height, int width) {
    for(int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = false;
        }
    }
}
void reset2DArray(int** grid, int height, int width) {
    for(int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = 0;
        }
    }
}

void destroy2DArray(bool** grid, int height, int width) {

    for(int i = 0; i < height; ++i) {
        delete [] grid[i];
    }
    delete [] grid;
}
void destroy2DArray(int** grid, int height, int width) {

    for(int i = 0; i < height; ++i) {
        delete [] grid[i];
    }
    delete [] grid;
}
