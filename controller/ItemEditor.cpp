
#include <vector>
#include <string>
#include <fstream>

#include "ItemEditor.h"
#include "../entity/Enhancement.h"
#include "../entity/ItemContainer.h"
#include "../utils/IOUtils.h"
#include "../entity/repo/ItemRepository.h"

using namespace std;


ItemEditor::ItemEditor()
{

}

void ItemEditor::editorAlternatives() {

    bool quit = false;

    cout << "\n\n************* Item Editor *************" << endl << endl;

    do {
    cout << "Please select an option:" << endl;
    cout << "1. Create an item" << endl;
    cout << "2. Edit an existing item" << endl;
    cout << "3. Exit" << endl;

    int choice = readIntegerInputWithRange("Your choice[1]: ", 1, 1, 3);

        switch (choice) {
            case 1:
                this->createItem();
                break;
            case 2:
                cout << "To be implemented" << endl;
                break;
            case 3:
                quit = true;
        }

    } while (!quit);
}


void ItemEditor::createItem() {

	cout << "\n************* Create Itenm *************" << endl << endl;

	do {


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

		bool intelligence =false, wisdom = false, armor = false, strength = false, constitution = false, charisma = false, dexterity = false, atkBonus = false, atkDamage = false;


		if (choice == 1)
		{
			itemType = "Armor";
			cout << "What is the name of your Armor" << endl;
			cin >> itemName;

			do
			{
				cout << "Please enter the type of ability you want to enhance for the Armor (ArmorC)" << endl;
				cin >> enhancementType;
			} while (enhancementType != "ArmorC");
			if (enhancementType == "ArmorC")
				armor = true;
			typeEnhancements.push_back(enhancementType);
			do
			{
				cout << "Please enter the Armor enhancement level you want ranging from 1 to 5 " << endl;
				cin >> armorBonus;
			} while (armorBonus < 1 || armorBonus > 5);

			bonus.push_back(armorBonus);
		}
		else if (choice == 2)
		{
			int i = 0;
			itemType = "Ring";
			cout << "What is the name of your Ring" << endl;
			cin >> itemName;
			do
			{
				do
				{
					cout << "please enter the type of ability you want to enhance for the Ring (";
					if (armor == false)
						cout << "ArmorC-";
					if (strength == false)
						cout << "Strength-";
					if (constitution == false)
						cout << "Constitution-";
					if (wisdom == false)
						cout << "Wisdom-";
					if (charisma == false)
						cout << "Charisma";
					cout << ")" << endl;
					cin >> enhancementType;
				} while (enhancementType != "ArmorC" && enhancementType != "Strength" && enhancementType != "Constitution" && enhancementType != "Wisdom" && enhancementType != "Charisma");

				if (enhancementType == "Strength")
					strength = true;
				else if (enhancementType == "Wisdom")
					wisdom = true;
				else if (enhancementType == "ArmorC")
					armor = true;
				else if (enhancementType == "Constitution")
					constitution = true;
				else if (enhancementType == "Charisma")
					charisma = true;
				typeEnhancements.push_back(enhancementType);
				do
				{
					cout << "Please enter the Ring enhancement level you want, ranging from 1 to 5" << endl;
					cin >> ringBonus;
				} while (ringBonus < 1 || ringBonus > 5);
				bonus.push_back(ringBonus);
				if (armor == true && strength == true && constitution == true && wisdom == true && charisma == true)
					answer = 'n';
				else
					cout << "Would like to add another enhancement?(y/n)" << endl;
					cin >> answer;
			} while (answer == "y");

			strength = false;
			wisdom = false;
			armor = false;
			constitution = false;
			charisma = false;

		}
		else if (choice == 3)
		{
			int i = 0;
			itemType = "Helmet";
			cout << "What is the name of your Helmet" << endl;
			cin >> itemName;
			do
			{
				do
				{
					cout << "please enter the type of ability you want to enhance for the Helmet  (";
					if (intelligence == false)
						cout << "Intelligence-";
					if (wisdom == false)
						cout << "Wisdom-";
					if (armor == false)
						cout << "ArmorC";
					cout << ")" << endl;
					cin >> enhancementType;
				} while (enhancementType != "Intelligence" && enhancementType != "Wisdom" && enhancementType != "ArmorC");

				if (enhancementType == "Intelligence")
					intelligence = true;
				else if (enhancementType == "Wisdom")
					wisdom = true;
				else if (enhancementType == "ArmorC")
					armor = true;
				typeEnhancements.push_back(enhancementType);
				do
				{
					cout << "Please enter the Helmet enhancement level you want ranging from 1 to 5 " << endl;
					cin >> helmetBonus;
				} while (helmetBonus < 1 || helmetBonus > 5);
				bonus.push_back(helmetBonus);
				if (intelligence == true && wisdom == true && armor == true)
					answer = 'n';
				else
					cout << "Would like to add another enhancement?(y/n)" << endl;
					cin >> answer;

			} while (answer == "y");

			intelligence = false;
			wisdom = false;
			armor = false;
		}
		else if (choice == 4)
		{
			int i = 0;
			itemType = "Boots";
			cout << "What is the name of your Boots" << endl;
			cin >> itemName;
			do {
				do {
					cout << "please enter the type of ability you want to enhance Boots(";
					if (armor == false)
						cout << "ArmorC-";
					if (dexterity == false)
						cout << "Dexterity";
					cout << ")" << endl;
					cin >> enhancementType;
					}while (enhancementType != "ArmorC" && enhancementType != "Dexterity");

					if (enhancementType == "ArmorC")
						armor = true;
					else if (enhancementType == "Dexterity")
						dexterity = true;
					typeEnhancements.push_back(enhancementType);
					do
					{
						cout << "Please enter the Boots enhancement level you want, ranging from 1 to 5" <<  endl;
						cin >> bootsBonus;
					} while (bootsBonus < 1 || bootsBonus > 5);

					bonus.push_back(bootsBonus);
					if (armor == true && dexterity == true)
						answer = 'n';
					else
						cout << "Would like to add another enhancement?(y/n)" << endl;
						cin >> answer;
 			} while (answer == "y");

			armor = false;
			dexterity = false;


		}
		else if (choice == 5)
		{
			int i = 0;
			itemType = "Belt";
			cout << "What is the name of your Belt" << endl;
			cin >> itemName;
			do {
				do {
					cout << "please enter the type of ability you want to enhance for Belt (";
					if (constitution == false)
						cout << "Consitution-";
					if (strength == false)
						cout << "Strength";
					cout << ")" << endl;
					cin >> enhancementType;
				} while (enhancementType != "Constitution" && enhancementType != "Strength");

				if (enhancementType == "Constitution")
					constitution = true;
				else if (enhancementType == "Strength")
					strength = true;
				typeEnhancements.push_back(enhancementType);
				do {
					cout << "Please enter the Belt enhancement level you want ranging from 1 to 5 " << endl;
					cin >> beltBonus;

				} while (beltBonus < 1 || beltBonus > 5);

				bonus.push_back(beltBonus);
				if (constitution == true && strength == true)
					answer = 'n';
				else
					cout << "Would like to add another enhancement?(y/n)" << endl;
					cin >> answer;
			} while (answer == "y");

		}
		else if (choice == 6)

		{
			int i = 0;
			itemType = "Weapon";
			cout << "What is the name of your Weapon" << endl;
			cin >> itemName;
			do
			{
				do
				{
					cout << "please enter the type of ability you want to enhance for the Weapon(";
					if (atkBonus == false)
						cout << "AtkBonus-";
				    if (atkDamage == false)
						cout << "AtkDamage";
					cout << ")" << endl;
					cin >> enhancementType;
				} while (enhancementType != "AtkBonus" && enhancementType != "AtkDamage");
				if (enhancementType == "AtkBonus")
					atkBonus = true;
				if (enhancementType == "AtkDamage")
					atkDamage = true;
				typeEnhancements.push_back(enhancementType);
				do
				{
					cout << "Please enter the Sword enhancement level you want ranging from 1 to 5 " << endl;
					cin >> swordBonus;
				} while (swordBonus < 1 || swordBonus > 5);
				bonus.push_back(swordBonus);
				if (atkBonus == true && atkDamage == true)
					answer = 'n';
				else
					cout << "Would like to add another enhancement?(y/n)" << endl;
					cin >> answer;
			} while (answer == "y");

		}
		else if (choice == 7)
		{
			int i = 0;
			itemType = "Shield";
			cout << "What is the name of your Shield" << endl;
			cin >> itemName;
			do
			{
				do
				{
					cout << "please enter the type of ability you want to enhance for shield (ArmorC) " << endl;
					cin >> enhancementType;
				} while (enhancementType != "ArmorC");
				typeEnhancements.push_back(enhancementType);
				do
				{
					cout << "Please enter the Shield enhancement level you want ranging from 1 to 5 " << endl;
					cin >> shieldBonus;
				} while (shieldBonus < 1 || shieldBonus > 5);
				bonus.push_back(shieldBonus);
			} while (answer == "y");

		}
//		else if (choice == 8)
//		{
//			cout << "Please enter the name of the file you want to load " << endl;
//			cin >> load;
//			backpack = loadFile(load);
//			break;
//		}
//		else if (choice == 9)
//		{
//			cout << "enter the save name " << endl;
//			cin >> save;
//
//			saveFile(save);
//			break;
//		}
		else if ( choice == 8)
		{
			break;

		}

		for(size_t i = 0; i < typeEnhancements.size(); ++i){
			Enhancements.push_back(Enhancement(typeEnhancements.at(i), bonus.at(i)));
		}
		while(!enhancementType.empty()){
			typeEnhancements.pop_back();
			bonus.pop_back();
		}

		Item* item = new Item(itemType, Enhancements, itemName);

        // TODO: Extract in display method in item class
        // START EXTRACTION
		vector<Enhancement> eVec = item->getInfluences();
        cout << "Item Type: " << item->getType() << endl;
        cout << "\tItem Name: " << item->getName() << endl;
        for (size_t i = 0; i<eVec.size(); i++) {
            cout << "\tEnhancement Type: " << eVec[i].getType() << "\n\tBonus Value: " << eVec[i].getBonus() << endl;
        }
        // END EXTRACTION

		while (!Enhancements.empty())
		{
			Enhancements.pop_back();
		}

		if (readYesNoInput("Would you like to save your newly created item?[Y/n]: ", true)) {
            ItemRepository::instance()->save(item->getName(), item);
		}

	} while (readYesNoInput("Would you like to create another item?[Y/n]: ", true));

}


//destructor
ItemEditor::~ItemEditor()
{

}

// TODO: is it still needed?

//void ItemEditor::readItem(ItemContainer* backpack, string name, ItemContainer* wornItems) {
//
//	string equipOrGoBack, itemToEquip;
//	if (name == "bp") {
//		//backpack->displayItem();
//		cout << "1 - Equip an item" << endl;
//		cout << "2 - Go back to game" << endl;
//		cin >> equipOrGoBack;
//		readIntegerInputWithRange(equipOrGoBack, 2, 1, 2);
//		if (equipOrGoBack == "1")
//		{
//			cout << "Please enter the name of the Item you wish to equip >> ";
//			cin >> itemToEquip;
//			//wornItems->equipItem(backpack, itemToEquip);
//		}
//		else if (equipOrGoBack == "2"){
//
//		}
//
//	}
//	if (name == "e") {
//		cout << "please enter the name of the Item you wish to equip >> ";
//		//wornItems->displayItem();
//	}
//}

