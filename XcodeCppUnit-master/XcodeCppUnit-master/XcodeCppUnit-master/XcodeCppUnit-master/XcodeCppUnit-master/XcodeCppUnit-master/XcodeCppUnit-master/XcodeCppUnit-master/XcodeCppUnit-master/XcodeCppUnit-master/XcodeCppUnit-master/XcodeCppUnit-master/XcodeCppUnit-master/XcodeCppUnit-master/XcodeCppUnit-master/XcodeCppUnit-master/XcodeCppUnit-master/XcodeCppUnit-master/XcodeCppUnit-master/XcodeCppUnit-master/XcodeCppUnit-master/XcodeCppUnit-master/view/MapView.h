/// @file
/// @brief Header file containing class declaration for MapRenderer.class
/// @details  1. Game Rules: No specific game rule enforced by the class. \n\n
/// 2. Design: View of the MVC pattern. Implements a Command Line Interface View of the Map. \n\n
/// 3. Libraries: No specific library is used apart from the iostream in order to display the map on the console

#pragma once

#include "../entity/Cell.h"
#include "../entity/Map.h"

/// Class that implements logic to render map in command line interface
class MapView {
    public:
        static void renderMap(Map* map);
    private:
        static void displayHeaderNavigation(int charsWidth, int cellWidth);
        static void displayLeftMargin(bool displayNavigation, int n, int margin);
};


