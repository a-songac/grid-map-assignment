#define RUN_TESTS

#include <iostream>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "entity/Cell.h"
#include "entity/Map.h"
#include "view/MapView.h"
#include "controller/MapEditorController.h"
#include "utils/IOUtils.h"


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

    cout << "*********** Choose an Editor ************" << endl << endl;
    cout << "Map Editor: 1"<< endl << "Campaign Editor: 2" << endl;
    int eChoice = readIntegerInput("",1);
    
    //Return chosen editor
    if(eChoice == 1){
        cout << "************** Map Creator **************" << endl << endl;
        
        cout << "Please select one of the following options:" << endl << "Create New Map: 1"
        << endl << "Edit an Existing Map: 2" << endl;
        
        int cChoice = readIntegerInput("", 1);
        
        //Create or edit Map
        if (cChoice == 1){
            MapEditorController mapEditor;
            Map* map = mapEditor.createMap();
            mapEditor.buildMap();
            
            bool save = readYesNoInput("Would you like to save this map? (Y/n)","Y");
            
            if(save){
                
            }
            else{
                //Back to choose editor
            }
        }
        else{
            
        }
    }
    else{
        cout << "*********** Campaign Creator ************" << endl << endl;
    }
    

    MapEditorController mapEditor;
    Map* map = mapEditor.createMap();
    mapEditor.buildMap();


    return 0;
}
