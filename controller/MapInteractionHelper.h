#pragma once

#include "../entity/Map.h"
#include "../controller/ItemEditor.h"

class MapInteractionHelper {
    public:
        static Coordinate readMapLocation(Map* map, string message, string defaultLocation);

    private:
        MapInteractionHelper();


};
