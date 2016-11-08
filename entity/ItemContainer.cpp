//! @file
//! @brief Implementation file for the ItemContainer class
//!

#include "ItemContainer.h"
#include "Enhancement.h"
#include "Character.h"
#include <iostream>
//! default constructor
ItemContainer::ItemContainer()
{
	Items = vector<Item>();
}

//! constructor that takes a vector of items as input to create an ItemContainer
//! @param containeritems: vector of items to put in the new container
ItemContainer::ItemContainer( vector<Item> containeritems)
{
	Items = containeritems;
}

//! method to get the items of the container
//! @return : return the vector of items contained in the ItemContainer
vector<Item> ItemContainer::getItems()
{
	return Items;
}

//! method to add an item to the item containerm
//! @param anitem : new item to put in the ItemContainer
void ItemContainer::addItemToBackpack(Item anitem)
{

	Items.push_back(anitem);

}
void ItemContainer::removeItemFromBackpack(Item anitem) {

	for (size_t i = 0; i < Items.size(); i++){
		if (Items[i].getName() == anitem.getName()) {
			Items.erase(Items.begin() + i);
		}

	}

}

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

void ItemContainer::equipItem(ItemContainer* backpack, Item anitem) {
	vector<Item> iVec = backpack->getItems();

	for (size_t i = 0; i < iVec.size(); ++i) {
		string name = iVec[i].getName();
		if (checkIfItemExists(anitem, name))
		{
			if (validateContainer()) {
				Items.push_back(anitem);

				cout << "you are now equipped with: " << anitem.getName() << endl;
				backpack->removeItemFromBackpack(anitem);

			}
		}
		else {
			cout << "You cannot equip Item: " << anitem.getName()  << endl;
		}

	}
}

void ItemContainer::unequipItem(ItemContainer* backpack, Item anitem) {

	for (size_t i = 0; i < Items.size(); i++)
	{
		if (checkIfItemExists(Items[i],anitem.getName()))
		{
			Items.erase(Items.begin() + i);

			cout << "Item: " << anitem.getName() << "has been successfully unequipped" << endl;
			backpack->addItemToBackpack(anitem);

		}
		else {
			if (i + 1 == Items.size()) {
				cout << "Item: " << anitem.getName() << "is not available" << endl;
			}
		}
	}
}

/*void ItemContainer::Enhancement::addEnhancement(Item anitem) {


	vector<Enhancement> eVec = anitem.getInfluences();
	for (size_t i = 0; i<eVec.size(); i++) {
		type = eVec[i].getType();
		bonus = eVec[i].getBonus();
		if (anitem.getType() == "Helmet") {

		}
		else if (anitem.getType() == "Armor") {

		}
		else if (anitem.getType() == "Shield") {

		}
		else if (anitem.getType() == "Ring") {

		}
		else if (anitem.getType() == "Belt") {

		}
		else if (anitem.getType() == "Boots") {

		}
		else if (anitem.getType() == "Weapon") {

		}
	}

}
*/
bool ItemContainer::checkIfItemExists(Item anitem, string name) {

		if (anitem.getType() == "Helmet" && anitem.getName() == name) {
			return true;
		}
		else if (anitem.getType() == "Armor" && anitem.getName() == name) {
			return true;
		}
		else if (anitem.getType() == "Shield" && anitem.getName() == name) {
			return true;
		}
		else if (anitem.getType() == "Ring" && anitem.getName() == name) {
			return true;
		}
		else if (anitem.getType() == "Belt" && anitem.getName() == name) {
			return true;
		}
		else if (anitem.getType() == "Boots" && anitem.getName() == name) {
			return true;
		}
		else if (anitem.getType() == "Weapon" && anitem.getName() == name) {
			return true;
		}

	return false;

}
//! method to validate a container, e.g. verify that an ItemContainer only contains a maximum of 1 item of each type (will be used for worn items container)
//! @return : true if the Items list is valid according to the rules, false if not
bool ItemContainer::validateContainer()
{
	int helmetCtr=0;
	int armorCtr=0;
	int shieldCtr=0;
	int ringCtr=0;
	int beltCtr=0;
	int bootsCtr=0;
	int weaponCtr=0;

	for (size_t i = 0; i < Items.size(); i++){
		if(Items[i].getType() == "Helmet"){
			helmetCtr++;
		}
		else if(Items[i].getType() == "Armor"){
			armorCtr++;
		}
		else if(Items[i].getType() == "Shield"){
			shieldCtr++;
		}
		else if(Items[i].getType() == "Ring"){
			ringCtr++;
		}
		else if(Items[i].getType() == "Belt"){
			beltCtr++;
		}
		else if(Items[i].getType() == "Boots"){
			bootsCtr++;
		}
		else if (Items[i].getType() == "Weapon"){
			weaponCtr++;
		}
	}

	if(helmetCtr>1 || armorCtr>1 || shieldCtr>1 || ringCtr>1 || beltCtr>1 || bootsCtr>1 || weaponCtr>1){
		return false;
	}
	else{
		return true;
	}

}
