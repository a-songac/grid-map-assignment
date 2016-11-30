
#include <vector>
#include <string>
#include <fstream>

#include "ItemEditor.h"
#include "../entity/Enhancement.h"
#include "../entity/ItemContainer.h"
#include "../utils/IOUtils.h"
#include "../entity/repo/ItemRepository.h"
#include "ItemInteractionHelper.h"

using namespace std;
ItemEditor::ItemEditor()
{

}

void ItemEditor::editorAlternatives() {

    bool quit = false, armorC = false;
    cout << "\n\n************* Item Editor *************" << endl << endl;

    do {
    cout << "Please select an option:" << endl;
    cout << "1. Create an item" << endl;
    cout << "2. View an existing item" << endl;
    cout << "3. Exit" << endl;

    int choice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 3);

        switch (choice) {
            case 1:
                this->createItem();
                break;
            case 2:
                Item* item;
                item = ItemInteractionHelper::selectItem();
                break;
            case 3:
                quit = true;
                break;
        }

    } while (!quit);
}


void ItemEditor::createItem() {
	bool quit = false;
	Item* item = new Item();
	do {
		cout << "************* Create Item *************" << endl << endl;
		Item* item = new Item();

		cout << "Please chose a number from the list below :" << endl;
		cout << "1. Create an Armor" << endl;
        cout << "2. Create a Ring " << endl;
        cout << "3. Create a Helmet " << endl;
        cout << "4. Create Boots " << endl;
        cout << "5. Create a Belt" << endl;
        cout << "6. Create a Weapon " << endl;
        cout << "7. Create a Shield" << endl;
        cout << "8. Exit" << endl;

		choice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 8);

		switch (choice) {
		case 1:
			item = this->armor();
			break;
		case 2:
			item = this->ring();
			break;
		case 3:
			item = this->helmet();
			break;
		case 4:
			item = this->boots();
			break;
		case 5:
			item = this->belt();
			break;
		case 6:
			item = this->weapon();
			break;
		case 7:
			item = this->shield();
			break;

		}
		if (choice == 8) {
			quit = true;
			break;
		}
		else {
			item->displayItem();
			if (readYesNoInput("Would you like to save your newly created item?[Y/n]: ", true)) {
				ItemRepository::instance()->save(item->getName(), item);
			} else {
                delete item;
			}
		}

	} while (readYesNoInput("Would you like to create another item?[Y/n]: ", true) && !quit);

}

Item* ItemEditor::armor() {


	itemType = "Armor";
	enhancementType = "ArmorC";

	itemName = readStringInputNoEmpty("Select a name for you Armor: ");
	armorBonus = readIntegerInputWithRange("Select an enhancement level, ranging from 1 to 5 [1]: ", 1, 1, 5);
	typeEnhancements.push_back(enhancementType);
	bonus.push_back(armorBonus);
	Enhancements.push_back(Enhancement(typeEnhancements[0], bonus[0]));
	Item* armorItem = new Item(itemType, Enhancements, itemName);
	Enhancements.clear();
	typeEnhancements.clear();
	bonus.clear();
	return armorItem;

}
Item* ItemEditor::ring() {
	armorC = 0;
	strength = 0;
	constitution = 0;
	wisdom = 0;
	charisma = 0;
	itemType = "Ring";
	itemName = readStringInputNoEmpty("Select a name for your Ring: ");

	do
	{
		isEnhancementsFull = false;
		do {
			retry = false;
			cout << endl;
			cout << "Please Select an option: " << endl;
			cout << "1. ArmorC" << endl;
			cout << "2. Strength" << endl;
			cout << "3. Constitution" << endl;
			cout << "4. Wisdom" << endl;
			cout << "5. Charisma" << endl;
			choice = readIntegerInputWithRange("Your choice: ", 1, 5);
			if (choice == 1 && armorC == 1 || choice == 2 && strength == 1 ||
				choice == 3 && constitution == 1 ||
				choice == 4 && wisdom == 1 || choice == 5 && charisma == 1)
			{
				cout << "You can select atmost one enhancement type" << endl;
				retry = true;
			}
		} while (retry);
		switch (choice)
		{
		case 1:
			enhancementType = "ArmorC";
			armorC = 1;
			break;
		case 2:
			enhancementType = "Strength";
			strength = 1;
			break;
		case 3:
			enhancementType = "Constitution";
			constitution = 1 ;
			break;
		case 4:
			enhancementType = "Wisdom";
			wisdom = 1;
			break;
		case 5:
			enhancementType = "Charisma";
			charisma = 1;
			break;
		}

		typeEnhancements.push_back(enhancementType);
		ringBonus = readIntegerInputWithRange("Select an enhancement level, ranging from 1 to 5 [1]: ", 1, 1, 5);
		bonus.push_back(ringBonus);
		if(armorC == 1 && strength == 1 && constitution == 1 && wisdom == 1 && charisma == 1) {
			isEnhancementsFull = true;
		}
		else {
			addEnhancement = readYesNoInput("Would you like to add another enhancement[Y/n]: ", true);
		}
	} while (addEnhancement && !isEnhancementsFull);
	for (size_t i = 0; i < typeEnhancements.size(); i++)
	{
		Enhancements.push_back(Enhancement(typeEnhancements[i], bonus[i]));
	}
	Item* ringItem = new Item(itemType, Enhancements, itemName);
	Enhancements.clear();
	typeEnhancements.clear();
	bonus.clear();
	return ringItem;
}
Item* ItemEditor::helmet() {
	armorC = 0;
	wisdom = 0;
	intelligence = 0;
	itemType = "Helmet";
	itemName = readStringInputNoEmpty("Select a name Helmet: ");
	do
	{
		isEnhancementsFull = false;
		do
		{
			retry = false;
			cout << "Please Select an option: " << endl;
			cout << "1. ArmorC" << endl;
			cout << "2. Wisdom" << endl;
			cout << "3. Intelligence" << endl;
			choice = readIntegerInputWithRange("Your choice[1]: ", 1, 3);
			if (choice == 1 && armorC == 1 || choice == 2 && wisdom == 1 ||
				choice == 3 && intelligence == 1)
			{
				cout << "You can select atmost one enhancement type" << endl;
				retry = true;
			}
		} while (retry);

		switch (choice)
		{
		case 1:
			enhancementType = "ArmorC";
			armorC = 1;
			break;
		case 2:
			enhancementType = "Wisdom";
			wisdom = 1;
			break;
		case 3:
			enhancementType = "Intelligence";
			intelligence = 1;
			break;
		}
		typeEnhancements.push_back(enhancementType);
		helmetBonus = readIntegerInputWithRange("Select an enhancement level, ranging from 1 to 5 [1]: ", 1, 1, 5);
		bonus.push_back(helmetBonus);
		if (armorC == 1 && wisdom == 1 && intelligence == 1) {
			isEnhancementsFull = true;
		}
		else {
			addEnhancement = readYesNoInput("Would you like to add another enhancement[Y/n]: ", true);
		}
	} while (addEnhancement && !isEnhancementsFull);

	for (size_t i = 0; i < typeEnhancements.size(); i++)
	{
		Enhancements.push_back(Enhancement(typeEnhancements[i], bonus[i]));
	}
	Item* helmetItem = new Item(itemType, Enhancements, itemName);
	Enhancements.clear();
	typeEnhancements.clear();
	bonus.clear();
	return helmetItem;
}

Item* ItemEditor::boots() {

	armorC = 0;
	dexterity = 0;

	itemType = "Boots";
	itemName = itemName = readStringInputNoEmpty("Select a name for your item with type Boots: ");
	do {
		isEnhancementsFull = false;
		do {
			retry = false;
			cout << "Please Select an option: " << endl;
			cout << "1. ArmorC" << endl;
			cout << "2. Dexterity" << endl;
			choice = readIntegerInputWithRange("Your choice[1]: ", 1, 2);
			if (choice == 1 && armorC == 1 || choice == 2 && dexterity == 1)
				{
					cout << "You can select atmost one enhancement type" << endl;
					retry = true;
				}
			} while (retry);
			switch (choice)
			{
			case 1:
				enhancementType = "ArmorC";
				armorC = 1;
				break;
			case 2:
				enhancementType = "Dexterity";
				dexterity = 1;
				break;
			}

			typeEnhancements.push_back(enhancementType);
			bootsBonus = readIntegerInputWithRange("Select an enhancement level, ranging from 1 to 5 [1]: ", 1, 1, 5);
			bonus.push_back(bootsBonus);
			if (armorC == 1 && dexterity == 1)
			{
				isEnhancementsFull = true;
			}
			else {
				addEnhancement = readYesNoInput("Would you like to add another enhancement[Y/n]: ", true);
			}

		} while (addEnhancement && !isEnhancementsFull);

		for (size_t i = 0; i < typeEnhancements.size(); i++)
		{
			Enhancements.push_back(Enhancement(typeEnhancements[i], bonus[i]));
		}

		Item* bootsItem = new Item(itemType, Enhancements, itemName);
		Enhancements.clear();
		typeEnhancements.clear();
		bonus.clear();
		return bootsItem;
}

Item* ItemEditor::belt() {

	strength = 0;
	constitution = 0;

	itemType = "Belt";
	itemName = itemName = readStringInputNoEmpty("Select a name for your item with type Belt: ");
	do {
		isEnhancementsFull = false;
		do {
			retry = false;
			cout << "Please Select an option: " << endl;
			cout << "1. Strength" << endl;
			cout << "2. Consitution" << endl;
			choice = readIntegerInputWithRange("Your choice[1]: ", 1, 2);
			if (choice == 1 && strength == 1 || choice == 2 && constitution == 1)
			{
				cout << "You can select atmost one enhancement type" << endl;
				retry = true;
			}
		} while (retry);

		switch (choice)
		{
		case 1:
			enhancementType = "Strength";
			strength = 1;
			break;
		case 2:
			enhancementType = "Consitution";
			constitution = 1;
			break;
		}

		typeEnhancements.push_back(enhancementType);
		helmetBonus = readIntegerInputWithRange("Select an enhancement level, ranging from 1 to 5 [1]: ", 1, 1, 5);
		bonus.push_back(helmetBonus);
		if (strength == 1 && constitution == 1)
		{
			isEnhancementsFull = true;
		}
		else {
			addEnhancement = readYesNoInput("Would you like to add another enhancement[Y/n]: ", true);
		}
	} while (addEnhancement && !isEnhancementsFull);
	for (size_t i = 0; i < typeEnhancements.size(); i++)
	{
		Enhancements.push_back(Enhancement(typeEnhancements[i], bonus[i]));
	}
	Item* beltItem = new Item(itemType, Enhancements, itemName);
	Enhancements.clear();
	typeEnhancements.clear();
	bonus.clear();
	return beltItem;
}

Item* ItemEditor::weapon() {

	atkBonus = 0;
	dmgBonus = 0;

	itemType = "Weapon";
	itemName = itemName = readStringInputNoEmpty("Select a name for your item with type weapon: ");
	do
	{
		isEnhancementsFull = false;
		do
		{
			retry = false;
			cout << "Please Select an option: " << endl;
			cout << "1. AtkBonus" << endl;
			cout << "2. DmgBonus" << endl;
			choice = readIntegerInputWithRange("Your choice[1]: ", 1, 2);
			if (choice == 1 && atkBonus == 1 || choice == 2 && dmgBonus == 1)
			{
				cout << "You can select atmost one enhancement type" << endl;
				retry = true;
			}
		} while (retry);
		switch (choice)
		{
		case 1:
			enhancementType = "AtkBonus";
			atkBonus = 1;
			break;
		case 2:
			enhancementType = "DmgBonus";
			dmgBonus = 1;
			break;
		}
		typeEnhancements.push_back(enhancementType);
		helmetBonus = readIntegerInputWithRange("Select an enhancement level, ranging from 1 to 5 [1]: ", 1, 1, 5);
		bonus.push_back(helmetBonus);
		if (atkBonus == 1 && dmgBonus == 1) {
			isEnhancementsFull = true;
		}
		else {
			addEnhancement = readYesNoInput("Would you like to add another enhancement[Y/n]: ", true);
		}
	} while (addEnhancement && !isEnhancementsFull);
	for (size_t i = 0; i < typeEnhancements.size(); i++)
	{
		Enhancements.push_back(Enhancement(typeEnhancements[i], bonus[i]));
	}
	Item* weaponItem = new Item(itemType, Enhancements, itemName);
	Enhancements.clear();
	typeEnhancements.clear();
	bonus.clear();
	return weaponItem;
}

Item* ItemEditor::shield() {


	itemType = "Shield";
	enhancementType = "ArmorC";
	itemName = readStringInputNoEmpty("What is the name of your Shield");
	armorBonus = readIntegerInputWithRange("Select an enhancement level, ranging from 1 to 5 [1]: ", 1, 1, 5);
	typeEnhancements.push_back(enhancementType);
	bonus.push_back(armorBonus);
	Enhancements.push_back(Enhancement(typeEnhancements[0], bonus[0]));
	Item* shielItem = new Item(itemType, Enhancements, itemName);
	Enhancements.clear();
	typeEnhancements.clear();
	bonus.clear();
	return shielItem;

}
//destructor
ItemEditor::~ItemEditor()
{

}

