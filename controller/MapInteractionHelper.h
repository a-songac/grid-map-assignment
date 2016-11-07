#pragma once

#include "../entity/Map.h"


class MapInteractionHelper {
    public:
        static Coordinate readMapLocation(Map* map, string message, string defaultLocation);

    private:
        MapInteractionHelper();


};
