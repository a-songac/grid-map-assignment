//! @file
//! @brief Implementation file for the MapTest class
//!
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "../src/entity/Map.h"
#include "../src/view/MapView.h"

using namespace CppUnit;

//! Test Class for the Map class
class MapTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MapTest);
	CPPUNIT_TEST(testMapCellFilled);
	CPPUNIT_TEST(testMapCellEmpty);
	CPPUNIT_TEST(testValidPath);
	CPPUNIT_TEST(testInvalidPath);
	CPPUNIT_TEST(testWallCell);
	CPPUNIT_TEST(testIsDoorCell);
	CPPUNIT_TEST(testFillCellFailure);
	CPPUNIT_TEST(testAttachMapObserver);
	CPPUNIT_TEST(testDetachMapObserver);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
protected:
	void testMapCellFilled();
	void testMapCellEmpty();
	void testValidPath();
	void testInvalidPath();
	void testWallCell();
	void testIsDoorCell();
	void testFillCellFailure();
	void testAttachMapObserver();
	void testDetachMapObserver();
private:
	Map *map;
};

//! cppunit registry creation
CPPUNIT_TEST_SUITE_REGISTRATION(MapTest);

//! method called before every test case in this test class
void MapTest::setUp()
{
	map = new Map();
}

//! method called after every test case in this test class
void MapTest::tearDown()
{
	delete map;
}

//! test method to test the isOccupied() method of the Map class
//! Test Case: the returned value should be true after filling the cell
//! Tested item: Map::isOccupied()
void MapTest::testMapCellFilled()
{
	// context: fill a cell
	map->fillCell(1, 1, 'a');
	//test: isOccupied() should return true after the cell having been filled
	CPPUNIT_ASSERT(true == map->isOccupied(1, 1));
}

//! test method to test the isOccupied() method of the Map class
//! Test Case: the returned value should be true after emptying the cell
//! Tested item: Map::isOccupied()
void MapTest::testMapCellEmpty()
{
	// context: make a cell empty
	map->fillCell(1, 1, ' ');
	// test: isOoccupied() should return false if the cell was not filled
	CPPUNIT_ASSERT(false == map->isOccupied(1, 1));
}

//! test method to test the validatePath() method of the Map class
//! Test Case: the returned value should be true if there is a valid path in the map
//! Tested item: Map::validatePath()
void MapTest::testValidPath()
{
	// context: create a map with a valid path
	// map as it is, is already valid

	// test: validatePath() should return true
	CPPUNIT_ASSERT(true == map->validate());
}

//! test method to test the validatePath() method of the Map class
//! Test Case: the returned value should be false if there is no valid path in the map
//! Tested item: Map::validatePath()
void MapTest::testInvalidPath()
{
	// context: create a map without a valid path: seperate entry and exit door by a wall
	for (int i = 0; i < map->getWidth(); i++) {

        CPPUNIT_ASSERT(true == map->validate());
        map->setCellType(2,i, Cell::TYPE_WALL);
	}

	// test: validatePath() should return false
	CPPUNIT_ASSERT(false == map->validate());
}

//! test method to test the isWall() method of the Map class
//! Test Case: the returned value should be true if the cell is of type wall
//! Tested item: Map::isWall()
void MapTest::testWallCell()
{
    map->setCellType(0,1, Cell::TYPE_WALL);

	// test: validatePath() should return false
	CPPUNIT_ASSERT(true == map->isWall(0,1));
}

//! test method to test the isWall() method of the Map class
//! Test Case: the returned value should be true if the cell is of type entry door or exit door
//! Tested item: Map::isDoor()
void MapTest::testIsDoorCell()
{

	// context: upper left corner and lower right cornor of the 7x7 are the entry and exit doors
	// test: is door should return true for bot coordinates
	CPPUNIT_ASSERT(true == map->isDoor(0,0));
	CPPUNIT_ASSERT(true == map->isDoor(6,6));
}

//! test method to test the fillCell() method of the Map class
//! Test Case: the returned value should be true if an occupant was successfully added on the cell
//! Tested item: Map::fillCell()
void MapTest::testFillCellFailure()
{

	// context: set a wall cell
	map->setCellType(0,1, Cell::TYPE_WALL);
	// test: fillCell should return false since the cell is actually a wall
	CPPUNIT_ASSERT(false == map->fillCell(0,1, Cell::OCCUPANT_FRIEND));
}

//! test method to test that the creation of an observer attaches an observer to the map
//! Test Case: the number of observers should be 1 after creating a mapview
//! Tested item: Map::attach() alled in MapView constructor
void MapTest::testAttachMapObserver()
{
    MapView mapView(map);
    CPPUNIT_ASSERT(1 == map->getNbObservers());

}

//! test method to test that the deletion of an observer detaches the observer from the map
//! Test Case: the number of obsers should be 0 after creating then deleting a mapview
//! Tested item: Map::detach() called in MapView destructor
void MapTest::testDetachMapObserver()
{
    MapView* mapView = new MapView(map);
    CPPUNIT_ASSERT(1 == map->getNbObservers());
    delete mapView;
    CPPUNIT_ASSERT(0 == map->getNbObservers());

}




