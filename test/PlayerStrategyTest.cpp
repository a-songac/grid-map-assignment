//! @file
//! @brief Implementation file for the PlayerStrategyTest class
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

#include "../entity/Map.h"
#include "../view/MapView.h"
#include "../service/FriendlyPlayerStrategy.h"
#include "../service/AggressivePlayerStrategy.h"

using namespace CppUnit;

//! Test Class for the Map class
class PlayerStrategyTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(PlayerStrategyTest);
	CPPUNIT_TEST(testCreationFriendlyCharacter);
	CPPUNIT_TEST(testCreationHostileCharacter);
	CPPUNIT_TEST(testPlayerMakeHostile);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
protected:
	void testCreationFriendlyCharacter();
    void testCreationHostileCharacter();
    void testPlayerMakeHostile();

private:
	GamePlayer player1;
	Coordinate* location;

};

//! cppunit registry creation
CPPUNIT_TEST_SUITE_REGISTRATION(PlayerStrategyTest);

//! method called before every test case in this test class
void PlayerStrategyTest::setUp()
{
    location = new Coordinate(1,1);
}

//! method called after every test case in this test class
void PlayerStrategyTest::tearDown()
{
    delete location;
}

//! test method to test that creating a friendly map character internally creates a Friendly Player Strategy
//! Test Case: the created player should have its instance of PlayerStrategy being type FriendlyPlayerStrategy
//! Tested item: GamePlayer::GamePlayer("dummy", location, Cell::OCCUPANT_FRIEND);
void PlayerStrategyTest::testCreationFriendlyCharacter()
{
	player1 = GamePlayer("dummy", location, Cell::OCCUPANT_FRIEND);
	FriendlyPlayerStrategy* friendly;
	friendly = dynamic_cast<FriendlyPlayerStrategy*> (player1.getActionStrategy());
	CPPUNIT_ASSERT(nullptr != friendly);

	AggressivePlayerStrategy* hostile;
	hostile = dynamic_cast<AggressivePlayerStrategy*> (player1.getActionStrategy());
	CPPUNIT_ASSERT(nullptr == hostile);
}

//! test method to test that creating a friendly map character internally creates a Hostile Player Strategy
//! Test Case: the created player should have its instance of PlayerStrategy being type AggressivePlayerStrategy
//! Tested item: GamePlayer::GamePlayer("dummy", location, Cell::OCCUPANT_OPPONENT);
void PlayerStrategyTest::testCreationHostileCharacter()
{
	player1 = GamePlayer("dummy", location, Cell::OCCUPANT_OPPONENT);
	FriendlyPlayerStrategy* friendly;
	friendly = dynamic_cast<FriendlyPlayerStrategy*> (player1.getActionStrategy());
	CPPUNIT_ASSERT(nullptr == friendly);

	AggressivePlayerStrategy* hostile;
	hostile = dynamic_cast<AggressivePlayerStrategy*> (player1.getActionStrategy());
	CPPUNIT_ASSERT(nullptr != hostile);
}



//! test method called when a player is attacked that makes its action strategy chance to hostile
//! Test Case: an attacked player that is friendly should become hostile
//! Tested item: GamePlayer::makeHostile();
void PlayerStrategyTest::testPlayerMakeHostile()
{
	player1 = GamePlayer("dummy", location, Cell::OCCUPANT_FRIEND);
	FriendlyPlayerStrategy* friendly;
	friendly = dynamic_cast<FriendlyPlayerStrategy*> (player1.getActionStrategy());
	CPPUNIT_ASSERT(nullptr != friendly);

	player1.makeHostile();

	friendly = dynamic_cast<FriendlyPlayerStrategy*> (player1.getActionStrategy());
	CPPUNIT_ASSERT(nullptr == friendly);

	AggressivePlayerStrategy* hostile;
	hostile = dynamic_cast<AggressivePlayerStrategy*> (player1.getActionStrategy());
	CPPUNIT_ASSERT(nullptr != hostile);
}




