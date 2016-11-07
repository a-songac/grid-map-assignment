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
#include "view/EditorView.h"


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


    EditorView::editorMenu();

    return 0;
}
