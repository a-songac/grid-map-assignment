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
