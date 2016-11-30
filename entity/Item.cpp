//! @file
//! @brief Implementation file for the Item class
//!

#include <iostream>
#include "Item.h"

//! default constructor
Item::Item()
{
	types = "";
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type, vector<Enhancement> influences,string type_name)
{
	// ***todo***: this constructor should verify that an new item of a certain type only
	// enhances a character statistic valid for this item type
	string iType = type;
	bool isValid = true;

	for (auto it = begin(influences); it != end(influences); ++it) {

		if (isValid == false) {
			break;
		}

		string eType = it->getType();

		if (iType == "Helmet") {
			if (eType == "Intelligence" || eType == "Wisdom" || eType == "ArmorC") {
				continue;
			}
			else {
				isValid = false;
			}
		}
		else if (iType == "Armor") {
			if (eType == "ArmorC") {
				continue;
			}
			else {
				isValid = false;
			}
		}
		else if (iType == "Shield") {
			if (eType == "ArmorC") {
				continue;
			}
			else {
				isValid = false;
			}
		}
		else if (iType == "Ring") {
			if (eType == "ArmorC" || eType == "Strength" || eType == "Constitution" || eType == "Wisdom" || eType == "Charisma") {
				continue;
			}
			else {
				isValid = false;
			}
		}
		else if (iType == "Belt") {
			if (eType == "Constitution" || eType == "Strength") {
				continue;
			}
			else {
				isValid = false;
			}
		}
		else if (iType == "Boots") {
			if (eType == "ArmorC" || eType == "Dexterity") {
				continue;
			}
			else {
				isValid = false;
			}
		}
		else if (iType == "Weapon") {
			if (eType == "AtkBonus" || eType == "DmgBonus") {
				continue;
			}
			else {
				isValid = false;
			}
		}
		else {
			isValid = false;
			cout << "Item type invalid.";
		}

	}

	if (isValid) {
		types = type;
		influence = influences;
		names = type_name;
	}
	else {
		cout << "Parameters for Item instantiation are invalid. Item " << type_name << " still created!" << endl;
		types = type;
		influence = influences;
		names = type_name;
	}

}

//! method to get the type of the item
//! @return : type of the item
string Item::getType()
{
	return types;
}
//! method to get the name  of the item
//! @return : name of the item
string Item::getName() {
	return names;
}
//! method to get the influences of the item
//! @return : vector containg the list of stats that the item enhances
vector<Enhancement> Item::getInfluences()
{
	return influence;
}

//! method to validate an item, e.g. verify that an new item of a certain type only enhances a character statistic valid for this item type
//! @return : true if the enhancement list is valid according to the rules, false if not
bool Item::validateItem()
{
	// ***todo***
	vector<Enhancement> eVec = this->getInfluences();
	string iType = this->getType();

	for (auto it = begin(eVec); it != end(eVec); ++it) {
		string eType = it->getType();

		if (it->getBonus()<1 || it->getBonus()>5) {
			return false;
		}
		else if (iType == "Helmet") {
			if (eType == "Intelligence" || eType == "Wisdom" || eType == "Armor") {

				continue;
			}
			else {
				return false;
			}
		}
		else if (iType == "Armor") {
			if (eType == "Armor") {
				continue;
			}
			else {
				return false;
			}
		}
		else if (iType == "Shield") {
			if (eType == "Armor") {
				continue;
			}
			else {
				return false;
			}
		}
		else if (iType == "Ring") {
			if (eType == "Armor" || eType == "Strength" || eType == "Constitution" || eType == "Wisdom" || eType == "Charisma") {
				continue;
			}
			else {
				return false;
			}
		}
		else if (iType == "Belt") {
			if (eType == "Constitution" || eType == "Strength") {
				continue;
			}
			else {
				return false;
			}
		}
		else if (iType == "Boots") {
			if (eType == "Armor" || eType == "Dexterity") {
				continue;
			}
			else {
				return false;
			}
		}
		else if (iType == "Weapon") {
			if (eType == "AtkBonus" || eType == "DmgBonus") {
				continue;
			}
			else {
				return false;
			}
		}
		else {
			cout << "Item type invalid.";
		}

	}



	return true;
}




void Item::displayItem()
{
    cout << endl << "============================================" << endl;
    vector<Enhancement> eVec = this->getInfluences();
    cout << "Item Type: " << this->getType() << endl;
    cout << "\tItem Name: " << this->getName() << endl;
    for (size_t i = 0; i<eVec.size(); i++) {
        cout << "\tEnhancement Type: " << eVec[i].getType() << endl;
    }
    cout << "============================================" << endl << endl;
}


