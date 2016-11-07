//! @file
//! @brief Implementation file for the CampaignTest class
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
#include "../src/entity/Campaign.h"
using namespace CppUnit;

//! Test Class for the Map class
class CampaignTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CampaignTest);
	CPPUNIT_TEST(testValidCampaign);
	CPPUNIT_TEST(testInvalidCampaign);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
protected:
	void testValidCampaign();
	void testInvalidCampaign();
private:
	Campaign *campaign;
};

//! cppunit registry creation
CPPUNIT_TEST_SUITE_REGISTRATION(CampaignTest);

//! method called before every test case in this test class
void MapTest::setUp()
{
	campaign = new Campaign();
}

//! method called after every test case in this test class
void MapTest::tearDown()
{
	delete campaign;
}


//! test method to test the validate() method of the Campaign class
//! Test Case: the returned value should be true if the campaign is non-empty
//! Tested item: Campaign::validate()
void MapTest::testValidCampaign()
{
	// context: create a campaign that is valid
    Map* map = new Map();
    vector<Map> m = this->campaign->getMaps();
    m.push_back(*map);
    Campaign* c = new Campaign(m);
    campaign->setCampaign(c);

	// test: validatePath() should return true
	CPPUNIT_ASSERT(true == campaign->validate());
}

//! test method to test the validate() method of the Campaign class
//! Test Case: the returned value should be false if the campaign is empty
//! Tested item: Campaign::validate()
void MapTest::testInvalidCampaign()
{
	// context: create an empty campaign (this is done by the default contructor)


	// test: validatePath() should return false
	CPPUNIT_ASSERT(false == campaign->validate());
}
