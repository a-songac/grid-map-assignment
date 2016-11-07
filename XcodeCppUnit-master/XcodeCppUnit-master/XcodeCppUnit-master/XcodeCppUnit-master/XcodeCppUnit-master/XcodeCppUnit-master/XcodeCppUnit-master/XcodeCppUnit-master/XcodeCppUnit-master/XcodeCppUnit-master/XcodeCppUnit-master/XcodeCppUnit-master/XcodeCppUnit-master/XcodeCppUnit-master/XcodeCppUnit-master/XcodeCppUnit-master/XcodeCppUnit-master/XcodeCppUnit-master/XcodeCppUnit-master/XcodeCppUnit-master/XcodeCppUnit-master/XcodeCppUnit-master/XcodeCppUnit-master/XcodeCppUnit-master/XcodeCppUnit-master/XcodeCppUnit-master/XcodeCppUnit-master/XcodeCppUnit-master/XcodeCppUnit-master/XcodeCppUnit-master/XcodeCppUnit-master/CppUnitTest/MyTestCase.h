//
//  MyTestCase.h
//  CppUnitTest
//
//  Created by shvns shvns on 12/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CppUnitTest_MyTestCase_h
#define CppUnitTest_MyTestCase_h

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class MyTestCase : public CppUnit::TestFixture
{
public:
    MyTestCase();
    ~MyTestCase();
    
public:
    void setUp();
    void tearDown();
    
    CPPUNIT_TEST_SUITE(MyTestCase);
    CPPUNIT_TEST(testFunction);
    CPPUNIT_TEST_SUITE_END();
    
public:
    void testFunction();
};



#endif
