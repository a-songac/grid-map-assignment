#pragma once
//! @file
//! @brief Header file for the Item class
//!This file contains the description of the Item class which is used to instantiate items.
//!An item is made up of a vector of Enhancements and has its own type. The class also contains
//! a default contructor, a parameterized constructor, a method to retrive the item type,
//! a method to retrieve the vector of enhancements of the item, and a method to validate an item.
//! The validate item method makes sure the enhancements correspond with the item type and that
//! enhancements have types and bonuses defined in the game rules. The libraries <string> and
//! <vector> were used to introduce the string and vector types for the type of the item and its
//! influences respectively. The Enhancement header file was also included for the influence vector
//! which is a vector of Enhancements.

#ifndef Item_h
#define Item_h

#include <string>
#include<vector>
#include "Enhancement.h"
using namespace std;

//! class for the implementation of items wearable by a character
class Item
{
public:
	// Default constructor
	Item();
	// Constructor
	Item(string type, vector<Enhancement> influences,string name);
	// method to get the type of the item
	string getType();
	//
	string getName();
	// method to get the influences of the item
	vector<Enhancement> getInfluences();
	//method to validate an item
	bool validateItem();

	void displayItem();
private:
	string types;
	vector<Enhancement> influence;
	string names;
};
#endif

