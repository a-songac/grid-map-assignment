#include <iostream>
#include "entity/Cell.h"
#include "entity/Map.h"
#include "service/MapRenderer.h"
#include "service/MapEditor.h"

using namespace std;

int main()
{
    cout << "************** Map Creator **************" << endl << endl;

    Map *map = new Map();
    MapEditor *mapEditor = new MapEditor(map);
    cout << "Generated Map: " << *map << endl;

    cout << "Display Map: " << endl << endl;
    MapRenderer::renderMap(map);

    mapEditor->buildMapContent();





    return 0;
}
