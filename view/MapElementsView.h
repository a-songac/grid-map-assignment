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

