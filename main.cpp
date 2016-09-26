#include <iostream>
#include "entity/Cell.h"
#include "entity/Map.h"
#include "service/MapRenderer.h"

using namespace std;

int main()
{
    cout << "************** Map Creator **************" << endl << endl;

    Map *map = new Map();
    cout << "Generated Map: " << *map << endl;

    cout << "Display Map: " << endl << endl;
    MapRenderer::renderMap(map);




    return 0;
}
