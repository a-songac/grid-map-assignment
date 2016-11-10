#pragma once
//! @file 
//! @brief Header file for the ItemContainer class  
//!This file contains the description of the ItemContainer class which is used to instantiate a container
//! of items. An ItemContainer is made up of a vector of Items. The class contains a default constructor,
//! a parameterized constructor, a method to retrieve the container's Item vector, a method to add an Item
//! to the container, a method to retrieve a particular item by its type, and a method to validate its contents.
//! In the implementation of this class the validate method verifies that the item container only contains a 
//! maximum of 1 item per item type. Later on different types of containers will need to be created with 
//! different limitations and therefore the validate method will be adapted to each type. The libraries 
//! <string> and <vector> were used to introduce the string and vector types for passing an item type to
//! the getItem() method and to create a vector of Items respectively. The Item header file was also included
//! since a vector of Items needed to be created.

#ifndef ItemContainer_h
#define ItemContainer_h

#include <string>
#include <vector>
#include "Enhancement.h"
#include "Item.h"
#include "../entity/Character.h"
using namespace std;

//! Class that implements an item container
class ItemContainer
{
public:
	// Default constructor
	ItemContainer();
	// Constructor
	ItemContainer(vector<Item> items);
	// method to get the items of the container
	vector<Item> getItems();
	// method to add an item to the item container
	void addItemToBackpack(Item anitem);
	//method to remove item from backpack
	void removeItemFromBackpack(Item anitem);
	// method to get an item from the item container
	Item* getItemFromBackpack(string itemType);
	//equip an item
	void equipItem(ItemContainer* backpack, string wearItem);
	//unequip an item
	void unequipItem(ItemContainer*, string wearItem);
	//check if Item exits in the backpack
	bool checkIfItemExists(string wearItem, string name);
	// method to validate container
	bool validateContainer();
	void displayItem();

private:
	vector<Item> Items;
};
#endif

