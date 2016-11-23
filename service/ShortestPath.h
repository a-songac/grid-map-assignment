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
