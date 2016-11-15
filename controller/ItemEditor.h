#pragma once
#pragma once
#include <iostream>

//#include "../entity/Item.h"
#include "../entity/Enhancement.h"
#include "../entity/ItemContainer.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class ItemEditor
{

public:
	ItemEditor();
	~ItemEditor();
	void editorAlternatives();
	void createItem();
	Item* armor();
	Item* helmet();
	Item* shield();
	Item* ring();
	Item* belt();
	Item* boots();
	Item* weapon();
	// TODO is it still needed
//	static void readItem(ItemContainer*, string name, ItemContainer*);

private:
	bool addEnhancement,retry, isEnhancementsFull;
	int i = 0;
	int choice;
	int armorBonus;
	int ringBonus;
	int helmetBonus;
	int swordBonus;
	int shieldBonus;
	int beltBonus;
	int bootsBonus;
	int armorC, strength, constitution, wisdom, charisma, intelligence, dexterity, atkBonus, dmgBonus;
	vector<int> bonus;
	vector<std::string> typeEnhancements;
	string save;
	string load;
	string itemType, enhancementType;
	string name;
	string itemName;
	string quit;
	
	Item item;
	Enhancement enhance;
	vector<Item> All_items;
	vector <Enhancement> Enhancements;




};

