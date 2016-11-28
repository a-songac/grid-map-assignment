/// @file
/// @brief
/// Header file for MapElementsView.class.  Observer of the map that displays information on the game elements of the map
/// Implements attack method.
///
/// @details
/// 1. Game Rules: A map has elements, namely items in chests, and friendly or hostile characters \n\n
/// 2. Design: Obsrver of the Map Subject \n\n
/// 3. Libraries: standard libraries: vector, string

#pragma once

#include "../entity/Cell.h"
#include "../entity/Map.h"

class MapElementsView : public Observer {
    public:
        MapElementsView(Map* map) : map(map) {
            this->map->Attach(this);
        }

        void update();

        void summary();
        void details();
    private:
        Map* map;

};

