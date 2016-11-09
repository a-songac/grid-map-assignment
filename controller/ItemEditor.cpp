
#include "ItemEditor.h"
#include "Enhancement.h"
#include "ItemContainer.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;


int i = 0;
string save;
string load;
static string typeEnhancements[5];
static int bonus[5];
string itemType, enhancementType;
string name;
string itemName;
string answer, quit;
ItemContainer* backpack = new ItemContainer();
ItemEditor::ItemEditor()
{

}

ItemContainer* ItemEditor::createItem() {

	ItemContainer* backpack = new ItemContainer();

	do {
	

		cout << "Please chose a number from the list below :" << endl;
		cout << "1-Create an Armor" << endl;
		cout << "2-Create a Ring " << endl;
		cout << "3-Create a Helmet " << endl;
		cout << "4-Create Boots " << endl;
		cout << "5-Create a Belt" << endl;
		cout << "6-Create a Weapon " << endl;
		cout << "7-Create a Shield" << endl;
		cout << "--------------------------" << endl;
		cout << "8- Load an item " << endl;
		cout << "9-Save item(s)" << endl;

		cin >> choice;
		
		bool intelligence =false, wisdom = false, armor = false, strength = false, constitution = false, charisma = false, dexterity = false, atkBonus = false, atkDamage = false;
	

		if (choice == 1)
		{
			itemType = "Armor";
				cout << "What is the name of your Armor" << endl;
				cin >> itemName;
				
					do {
						cout << "Please enter the type of ability you want to enhance for the Armor (Armor)" << endl;
						cin >> enhancementType;
					} while (enhancementType != "Armor");
					if (enhancementType == "Armor")
						armor = true;
					typeEnhancements[0] = enhancementType;
					do {
						cout << "Please enter the Armor enhancement level you want ranging from 1 to 5 " << endl;
						cin >> armorBonus;
					} while (armorBonus < 1 || armorBonus > 5);
					
				bonus[0] = armorBonus;
				
				
				
			

		}
		else if (choice == 2)
		{
			int i = 0;
			itemType = "Ring";
			cout << "What is the name of your Ring" << endl;
			cin >> itemName;
			do {
				do {
					cout << "please enter the type of ability you want to enhance for the Ring (";
					if (armor == false)
					{
						cout << "Armor-";
				
					}
					if (strength == false)
					{
						cout << "Strength-";
	
					}
					if (constitution == false)
					{
						cout << "Constitution-";
						
					}
					if (wisdom == false) {
						cout << "Wisdom-";
					
					}
					if (charisma == false) {
						cout << "Charisma";
					
					}
					cout << ")" << endl;
					cin >> enhancementType;
				} while (enhancementType != "Armor" && enhancementType != "Strength" && enhancementType != "Constitution" && enhancementType != "Wisdom" && enhancementType != "Charisma");

				if (enhancementType == "Strength")
					strength = true;
				else if (enhancementType == "Wisdom")
					wisdom = true;
				else if (enhancementType == "Armor")
					armor = true;
				else if (enhancementType == "Constitution")
					constitution = true;
				else if (enhancementType == "Charisma")
					charisma = true;
				typeEnhancements[i] = enhancementType;
				do {
					cout << "Please enter the Ring enhancement level you want, ranging from 1 to 5" << endl;
					cin >> ringBonus;
				} while (ringBonus < 1 || ringBonus > 5);
				bonus[i] = ringBonus;
				i++;
				if (armor == true && strength == true && constitution == true && wisdom == true && charisma == true) {
					answer = 'n';
				}
				else {
					cout << "Would like to add another enhancement?(y/n)" << endl;
					cin >> answer;
				}
			} while (answer == 'y');
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
			do {
				do {
					cout << "please enter the type of ability you want to enhance for the Helmet  (";
					if (intelligence == false)
					{
						cout << "Intelligence-";
						
					}
					if (wisdom == false)
					{
						cout << "Wisdom-";
						
					}
					if (armor == false) {
						cout << "Armor";
						
					}
					cout << ")" << endl;
					cin >> enhancementType;
				} while (enhancementType != "Intelligence" && enhancementType != "Wisdom" && enhancementType != "Armor");
				if (enhancementType == "Intelligence")
					intelligence = true;
				if (enhancementType == "Wisdom")
					wisdom = true;
				if (enhancementType == "Armor")
					armor = true;
				typeEnhancements[i] = enhancementType;
				do {
					cout << "Please enter the Helmet enhancement level you want ranging from 1 to 5 " << endl;
					cin >> helmetBonus;
				} while (helmetBonus < 1 || helmetBonus > 5);
				bonus[i] = helmetBonus;
				i++;

				if (intelligence == true && wisdom == true && armor == true)
				{
					answer = 'n';
				}
				else {
					cout << "Would like to add another enhancement?(y/n)" << endl;
					cin >> answer;
				}
				
			} while (answer == 'y');
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
					{
						cout << "Armor-";
						
					}
					if (dexterity == false) {
						cout << "Dexterity";
						
					}
						cout << ")" << endl;
						cin >> enhancementType;
					}while (enhancementType != "Armor" && enhancementType != "Dexterity");

					if (enhancementType == "Armor")
						armor = true;
					if (enhancementType == "Dexterity")
						dexterity = true;
					typeEnhancements[i] = enhancementType;
					do {
						cout << "Please enter the Boots enhancement level you want, ranging from 1 to 5" <<  endl;
						cin >> bootsBonus;
					} while (bootsBonus < 1 || bootsBonus > 5);
					bonus[i] = bootsBonus;
					i++;
					if (armor == true && dexterity == true) {
						answer = 'n';
					}
					else {
						cout << "Would like to add another enhancement?(y/n)" << endl;
						cin >> answer;
					}
 			} while (answer == 'y');
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
					if (constitution == false) {
						cout << "Consitution-";
						
					}
					if (strength == false) {
						cout << "Strength";
						
					}
					cout << ")" << endl;
					cin >> enhancementType;
				} while (enhancementType != "Constitution" && enhancementType != "Strength");
				if (enhancementType == "Constitution")
					constitution = true;
				if (enhancementType == "Strength")
					strength = true;
				typeEnhancements[i] = enhancementType;
				do {
					cout << "Please enter the Belt enhancement level you want ranging from 1 to 5 " << endl;
					cin >> beltBonus;
					
				} while (beltBonus < 1 || beltBonus > 5);
				bonus[i] = beltBonus;
				i++;
				if (constitution == true && strength == true) {
					answer = 'n';
				}
				else {
					cout << "Would like to add another enhancement?(y/n)" << endl;
					cin >> answer;
				}
			} while (answer == 'y');
			
		}
		else if (choice == 6)

		{
			int i = 0;
			itemType = "Weapon";
			cout << "What is the name of your Weapon" << endl;
			cin >> itemName;
			do {
				do {
					cout << "please enter the type of ability you want to enhance for the Weapon(";
					if (atkBonus == false) {
						cout << "AtkBonus-";
						
					}
				    if (atkDamage == false) {
						cout << "AtkDamage";
						
					}
					cout << ")" << endl;
					cin >> enhancementType;
					

				} while (enhancementType != "AtkBonus" && enhancementType != "AtkDamage");
				if (enhancementType == "AtkBonus")
					atkBonus = true;
				if (enhancementType == "AtkDamage")
					atkDamage = true;
				typeEnhancements[i] = enhancementType;
				do {
					cout << "Please enter the Sword enhancement level you want ranging from 1 to 5 " << endl;
					cin >> swordBonus;
				} while (swordBonus < 1 || swordBonus > 5);
				bonus[i] = swordBonus;
				i++;
				if (atkBonus == true && atkDamage == true)
					answer = 'n';
				else
				{
					cout << "Would like to add another enhancement?(y/n)" << endl;
					cin >> answer;
				}
			} while (answer == 'y');
			
		}
		else if (choice == 7)
		{
			int i = 0;
			itemType = "Shield";
			cout << "What is the name of your Shield" << endl;
			cin >> itemName;
			do {
				do {
					cout << "please enter the type of ability you want to enhance for shield (Only Armor) " << endl;
					cin >> enhancementType;
				} while (enhancementType != "Armor");
				typeEnhancements[0] = enhancementType;
				do {
					cout << "Please enter the Shield enhancement level you want ranging from 1 to 5 " << endl;
					cin >> shieldBonus;
				} while (shieldBonus < 1 || shieldBonus > 5);
				bonus[0] = shieldBonus;
			} while (answer == 'y');
	
		}
		else if (choice == 8)
		{

			cout << "Please enter the name of the file you want to load " << endl;
			cin >> load;
			backpack = loadFile(load);
			break;

		}
		else if (choice == 9)
		{
			cout << "enter the save name " << endl;
			cin >> save;

			saveFile(save);
			break;
		}
		else if (choice != 1 || choice != 2 || choice != 3 || choice != 4 || choice != 5 || choice != 6 || choice != 7 || choice != 8 || choice != 9)
		{
			cout << "Goodbye" << endl;

		}

		for (size_t i = 0; i < 5; i++)
		{
			Enhancements.push_back(Enhancement(typeEnhancements[i], bonus[i]));
			typeEnhancements[i].clear();
			if (bonus[i + 1] == 0) {
				bonus[i] = 0;
				break;
			}
			bonus[i] = 0;
		}
		

		Item item(itemType, Enhancements, itemName);
		backpack->addItemToBackpack(item);
		
		vector<Item> iVec = backpack->getItems();
		
		for (size_t i = 0; i < iVec.size(); ++i) {
		vector<Enhancement> eVec = iVec[i].getInfluences();
			cout << "Item Type: " << iVec[i].getType() << endl;
			cout << "\tItem Name: " << iVec[i].getName() << endl;
			for (size_t i = 0; i<eVec.size(); i++) {
				cout << "\tEnhancement Type: " << eVec[i].getType() << "\n\tBonus Value: " << eVec[i].getBonus() << endl;
			}
		}
		All_items.push_back(item);
		while (!Enhancements.empty())
		{
			Enhancements.pop_back();
		}


		cout << "Would you like to create an other item or to save (y/n)?" << endl;
		cin >> quit;


	} while (quit == "y" || quit == "Y");

	return backpack;
}

//saving
void ItemEditor::saveFile(string name)
{
	ofstream saveFile(name+".txt", std::ios::out);
	vector<Enhancement> eVec;

	for (size_t i = 0; i < All_items.size(); ++i)
	{
		saveFile << All_items[i].getType() << endl;
		saveFile << All_items[i].getName() << endl;
		eVec = All_items[i].getInfluences();

		for (size_t i = 0; i < eVec.size(); i++)
		{
			saveFile << eVec[i].getType() << endl;
			saveFile << eVec[i].getBonus() << endl;
			
		}

	}
	saveFile.close();

}

//loading
ItemContainer* ItemEditor::loadFile(string load)
{
	std::ifstream f(load, std::ios::in);

	if (f.is_open())
	{
		int bonus;
		string getBonus;
		int i = 0;
		
		getline(f, itemType);
		itemType = itemType;
		do {
			
			getline(f, itemName);
			getline(f, enhancementType);

			while (enhancementType != "Ring"  && enhancementType != "Helmet" && enhancementType != "Boots" && enhancementType!="Belt" && enhancementType!="Weapon" && enhancementType!="Shield" && enhancementType !="") 
			{
				getline(f, getBonus);
				bonus = std::stoi(getBonus);
				Enhancements.push_back(Enhancement(enhancementType, bonus));
				getline(f, enhancementType);
				i++;
			}
			i = 0;
			
			Item item(itemType, Enhancements, itemName);
			while (!Enhancements.empty())
			{
				Enhancements.pop_back();
			}

			backpack->addItemToBackpack(item);
			cout << item.getType() << " added to Backpack" << endl;
			itemType = enhancementType;
		} while (!f.eof());
		cout << "Items from " << load << " have been loaded successfully" << endl;
		return backpack;


	}
	f.close();
	return nullptr;
}
//destructor
ItemEditor::~ItemEditor()
{

}
