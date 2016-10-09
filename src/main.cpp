#include <iostream>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "entity/Cell.h"
#include "entity/Map.h"
#include "service/MapRenderer.h"
#include "service/MapEditor.h"

using namespace std;

int main()
{
    // Run tests prior to the execution of the driver
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);
    runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(), std::cerr ) );
    bool wasSucessful = runner.run();
    if (!wasSucessful) {
        return 0;
    }



    cout << "************** Map Creator **************" << endl << endl;

    MapEditor mapEditor;
    Map* map = mapEditor.createMap();
    mapEditor.buildMap();


    return 0;
}
