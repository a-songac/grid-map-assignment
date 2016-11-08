#pragma once
//! @file 
//! @brief Header file for the Enhancement class  
//!This file contains the description for an Enhancement which has two attributes, type and bonus.
//!The type ranges from intelligence to dmgBonus and bonus ranges from 1 to 5. Although any string and integer 
//! can be passed in the constructor as type and bonus respectively, these enhancements will be validated  
//! later on when they are contained within an item by the item method validateItem(). The class contains 
//! a default constructor, a parameterized constructor, a method to get the type of the enhancement, and 
//! a method to retrieve the bonus of the enhancement. The library <string> was used to introduce 
//! the string type which is used for the "type" variable of this class.

#ifndef Enhancement_h
#define Enhancement_h

#include <string>
using namespace std;

//! class for the implementation of an enhancement, i.e. a stat influenced by an item, as well as the bonus it gives
class Enhancement
{
public:
	// Default constructor
	Enhancement();
	// Constructor
	Enhancement(string type, int bonus);
	// method to get the type of the item
	string getType();
	// method to get the bonus of the type
	int getBonus();
	
private:
	string type;
	int bonus;
	
};
#endif

