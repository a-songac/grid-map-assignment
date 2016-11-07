/// @file
/// @brief Header file containing class declaration for MapValidator.class
/// @details  1. Game Rules: Enforces that all cells on the map are reachable from the entry door. \n\n
/// 2. Design: The class acts as a service. It encapsulates the logic to validate a map.  Concretely, it checks that
/// each non-wall cell can be reached from the entry door of the map using a recursive function.
/// The assumption is made that one can navigate from a cell to another in the following manner:
/// up, down, right or left.
/// To increase the performance of the algorithm, a cell not yet tested but that was used
/// in the path to reach the entry door while testing another cell, is flagged as reachable.
/// Consequently, this cell will be skipped when its turn comes for validation. \n\n
/// 3. Libraries: No specific library is used aprt from iostream.

#pragma once

#include "../entity/Map.h"

/// Class that implements the logic for validating a map.
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
