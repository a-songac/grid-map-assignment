#pragma once

#include "../entity/Map.h"

class MapValidator {
    public:

        MapValidator(Map* map);
        ~MapValidator();

        bool validateMap();


    private:

        Map* map;
        int** reachable;
        bool** visited;
        bool validateForDoor(int row, int column, Coordinate door);
        bool backTrack(int row, int column, int doorRow, int doorColumn);

};

void initialize2DArray(bool** grid, int height, int width);
void initialize2DArray(int** grid, int height, int width);
void reset2DArray(bool** grid, int height, int width);
void reset2DArray(int** grid, int height, int width);
void destroy2DArray(bool** grid, int height, int width);
void destroy2DArray(int** grid, int height, int width);
bool inbound(int i, int j, int height, int width);

