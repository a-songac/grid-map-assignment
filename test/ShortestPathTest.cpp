#include "ShortestPathTest.h"

#include "../entity/Map.h"
#include "../entity/repo/MapRepository.h"
#include "../controller/MapInteractionHelper.h"
#include "../utils/IOUtils.h"
#include "../service/ShortestPath.h"

#include <vector>

void ShortestPathTest::interactiveTest() {

    Map* map;
    Coordinate start;
    Coordinate destination;
    vector<Coordinate> path;

    do {

        cout << "\n\n ************ SHORTEST PATH INTERACTIVE TEST ************" << endl << endl;


        // /////////////////////
        // SELECT A MAP
        // ////////////////////
        bool confirm = false;
        string filename, name1;
        vector<string>* mapReferences = MapRepository::instance()->listAll();

        if(mapReferences->size() > 0){

            do {
                cout << "Please select a map: " << endl;
                for (size_t i = 0; i < mapReferences->size(); i++) {
                    cout << i+1 << ":" << mapReferences->at(i) << endl;
                }
                int index = readIntegerInputWithRange("Your selection[1]: ", 1, 1, mapReferences->size());

                map = MapRepository::instance()->getEntity(index-1);
                map->render();
                confirm = readYesNoInput("You confirm the selection of this map displayed above?[Y/n]: ", true);

            } while (!confirm);
        } else {
            cout << "Error could not load maps" << endl;
        }


        ShortestPath
        pathCalculator = ShortestPath(map);

        do {
            map->render();

            start = MapInteractionHelper::readMapLocation(map, "Select starting location: ", "");
            destination = MapInteractionHelper::readMapLocation(map, "Select destination location: ", "");

            path = pathCalculator.computeShortestPath(start, destination, false);
            map->render();
            cout << "Computed Shortest Path: " << endl;
            cout << "    length: " << path.size() << endl;
            cout << "    path: ";
            for (size_t i = 0; i < path.size(); i++) {
                cout << MapInteractionHelper::coordinateToString(path.at(i));
            }
            cout << endl << endl;


        } while (readYesNoInput("Continue testing on this map?[Y/n]: ", true));

    } while (readYesNoInput("Continue interactive testing?[Y/n]: ", true));


}
