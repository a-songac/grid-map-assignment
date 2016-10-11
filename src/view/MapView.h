/// @file
/// @brief Header file containing class declaration for MapRenderer.class
/// @details  No specific game rule enforced by the class.
/// The class provides a static methods to render the map in a command line interface.
/// It is used to avoid bloating the Map class
/// No specific library is used.

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


