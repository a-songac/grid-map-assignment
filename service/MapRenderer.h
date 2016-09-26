#pragma once

#include "../entity/Cell.h"
#include "../entity/Map.h"

class MapRenderer {
    public:
        static const int CELL_HEIGHT = 5;
        static const int CELL_WIDTH = 10;
        static const int LEFT_MARGIN = 5;
        static const string HORIZONTAL_BORDER;
        static const string VERTICAL_BORDER;
        static const string FLOOR;
        static const string WALL;
        static void renderMap(Map* map);

};

void displayHeaderNavigation(int charsWidth, int cellWidth);
void displayLeftMargin(bool displayNavigation, int n, int margin);

