#pragma once

#include "../entity/Map.h"

using namespace std;

class MapEditor {
    public:

        static const string ADD_WALL_PROMPT;
        static const string WALL_LOCATION_PROMPT;
        static const string CELL_LOCATION_REGEX;

        MapEditor();
        MapEditor(Map* map);

        void buildMapContent();
        void addWall();
        bool validateMap();
        bool backTrack(int row, int column, int entryRow, int entryColumn);
        bool inbound(int i, int j, int height, int width);

    private:
        Map* map;
        bool** reachable;
        bool** visited;



};

