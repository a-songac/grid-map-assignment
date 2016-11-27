#define RUN_TESTS
//#define RUN_TEST_MANUAL

#include <iostream>

#include "entity/Cell.h"
#include "entity/Map.h"
#include "view/MapView.h"
#include "controller/MapEditorController.h"
#include "utils/IOUtils.h"
#include "controller/EditorFacadeController.h"
#include "entity/repo/MapRepository.h"
#include "entity/repo/CharacterRepository.h"
#include "entity/repo/ItemRepository.h"
#include "entity/repo/GameRepository.h"
#include "utils/IOUtils.h"
#include "controller/GamePlayController.h"
#include "test/ShortestPathTest.h"

using namespace std;

int main()
{
    #ifdef RUN_TESTS

    #endif // RUN_TESTS



    MapRepository::instance();
    CharacterRepository::instance();
    ItemRepository::instance();
    GameRepository::instance();

    #ifdef RUN_TEST_MANUAL
        if (readYesNoInput("Test Shortest path algorithm?[Y/n]: ", true)) {
            ShortestPathTest::interactiveTest();
        }
    #endif // RUN_TEST_MANUAL


    int choice;
    bool gameLoop = true;

    do {


        cout << "\n\n********************* DONGONS AND DRAGONS *********************" << endl << endl;
        cout << "Please select an action: " << endl;
        cout << "1. Play Game" << endl;
        cout << "2. Edit Game Elements" << endl;
        cout << "3. Exit :(" << endl;
		choice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 3);


        switch (choice) {
            case 1:
            {
                GamePlayController gameController;
                gameController.newGame();
                break;
            }
            case 2:
            {
                EditorFacadeController::editorMenu();
                break;
            }
            case 3:
            {
                gameLoop = false;
                cout << "Good bye!" << endl;
                break;
            }
        }
    } while (gameLoop);

    return 0;
}
