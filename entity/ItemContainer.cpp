//! @file 
//! @brief Implementation file for the ItemContainer class  
//!
#include <iostream>

#include "ItemContainer.h"
#include "../controller/ItemEditor.h"

//! default constructor
//Character* c;
//vector<Item> ItemContainer::Items;
//ItemContainer::ItemContainer()
//{
//	Items = vector<Item>();
//}
//
////! constructor that takes a vector of items as input to create an ItemContainer
////! @param containeritems: vector of items to put in the new container
//ItemContainer::ItemContainer( vector<Item> containeritems)
//{
//	Items = containeritems;
//}

//! method to get the items of the container
//! @return : return the vector of items contained in the ItemContainer

//vector<Item> ItemContainer::getItems()
//{
//	return Items;
//}

//! method to add an item to the item containerm 
//! @param anitem : new item to put in the ItemContainer

/*
//! method to return the item of a certain type contained in the ItemContainer
//! assumption: the container can only contain one element of each type
//! @param itemType : type of item to extract from the container
//! @return : item of the specified kind provided in input
Item* ItemContainer::getItemFromBackpack(string itemType)
{
	for (size_t i = 0; i < Items.size(); i++)
		if (Items[i].getType() == itemType)
			return &(Items[i]);
	return nullptr;
	
}


void ItemContainer::unequipItem(ItemContainer* backpack, string name) {
	vector<Item> iVec = this->getItems();
	for (size_t i = 0; i < iVec.size(); ++i)
	{
		
		if (checkIfItemExists(iVec[i].getName() , name))
		{
			Items.erase(Items.begin() + i);
		
			cout << "Item: " <<iVec[i].getName() << " has been successfully unequipped" << endl;
			backpack->addItemToBackpack(iVec[i]);
			//c->updateStatsAtUnequip(iVec[i]);
		}
		else {
			if (i + 1 == Items.size()) {
				cout << "Item: " << iVec[i].getName() << " is not available" << endl; 
			}
		}
	}



bool ItemContainer::checkIfItemExists(string wearItem, string name) {

		if (wearItem == name) {
			return true;
		}

	return false;
	
}*/
//! method to validate a container, e.g. verify that an ItemContainer only contains a maximum of 1 item of each type (will be used for worn items container)  
//! @return : true if the Items list is valid according to the rules, false if not
