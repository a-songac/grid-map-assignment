/// @file
/// @brief
/// Header file for ShortestPath.class.  algorithm to compute shortest path between two locations on a map, considering the obstacles (walls and other players)
/// Implements attack method.
///
/// @details
/// 1. Game Rules: The navigation of characters on the map is limited by the walls and the other characters. \n\n
/// 2. Design: Concreteimplementation of a strategy for the PlayerStrategy. Derived from NonUserStrategy class \n\n
/// 3. Libraries: standard libraries: vector

#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <vector>>

#include "../entity/Cell.h"
#include "../entity/Map.h"


class ShortestPath
{
    public:
        ShortestPath(Map* map);
        ~ShortestPath();

        vector<Coordinate> computeShortestPath(Coordinate start , Coordinate destination, bool considerPlayers);
        void backTrack(int row, int column, int destinationRow, int destinationColumn, bool considerPlayers);

    protected:

    private:
        Map* map;
        Coordinate start;
        Coordinate destination;
        std::vector<Coordinate>* _currentPath;
        std::vector<Coordinate>* _shortestPath;
        unsigned int length;
        bool** visited;
};

#endif // SHORTESTPATH_H
