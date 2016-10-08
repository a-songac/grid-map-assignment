#include <iostream>

#include "entity/Cell.h"
#include "entity/Map.h"
#include "service/MapRenderer.h"
#include "service/MapEditor.h"

using namespace std;

int main()
{


    cout << "************** Map Creator **************" << endl << endl;

    MapEditor mapEditor;
    Map* map = mapEditor.createMap();
    mapEditor.buildMapContent();


    return 0;
}
