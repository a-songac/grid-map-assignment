#define RUN_TESTS
//#define RUN_TEST_MANUAL


#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

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
#include "entity/repo/CampaignRepository.h"
#include "utils/IOUtils.h"
#include "controller/GamePlayController.h"
#include "test/ShortestPathTest.h"
#include "../grid-map-assignment/controller/CharacterEditorController.h"
#include "../grid-map-assignment/entity/BullycharacterBuilder.h"
#include "../grid-map-assignment/entity/NimbleCharacterBuilder.h"
#include "../grid-map-assignment/entity/TankCharacterBuilder.h"
#include "../grid-map-assignment/entity/CharacterBuilder.h"
#include "../grid-map-assignment/entity/DDMaster.h"

using namespace std;

int main()
{
    #ifdef RUN_TESTS
        CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
        CppUnit::TextUi::TestRunner runner;
        runner.addTest(suite);
        runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(), std::cerr ) );
        bool wasSucessful = runner.run();
        if (!wasSucessful) {
            return 0;
        }

    #endif // RUN_TESTS
    MapRepository::instance();

    CharacterRepository::instance();
    ItemRepository::instance();
    GameRepository::instance();
    CampaignRepository::instance();

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
                cout << "********* PLAY GAME *********" << endl;
                cout << "1. Start a new game" << endl;
                cout << "2. Load previous game" << endl;
                int choice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 2);
                if (1 == choice)
                    gameController.newGame();
                else
                    gameController.loadGame();
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