#include <iostream>
#include <iomanip>

#include "CharacterView.h"
#include "../entity/Character.h"

using namespace std;

CharacterView::CharacterView() {

};

CharacterView::CharacterView(Character* c) {
	//Upon instantiation, attaches itself
	//to a ClockTimer

	_subject = c;
	_subject->Attach(this);
};

CharacterView::~CharacterView() {
	_subject->Detach(this);
};

void CharacterView::update() {

	display();
};

void CharacterView::display() {


		cout << "================================================================================" << endl;
		cout << "Level: " << _subject->getLevel() << endl;
		cout << "Strength: " << _subject->getStrength() << " (+" << _subject->getModStrength() << ")"<< endl;
		cout << "Dexterity: " << _subject->getDexterity() << " (+" << _subject->getModDexterity() << ")"  << endl;
		cout << "Intelligence: " << _subject->getIntelligence() << " (+" << _subject->getModIntelligence() << ")" << endl;
		cout << "Charisma: " << _subject->getCharisma() << " (+" << _subject->getModCharisma() << ")" << endl;
		cout << "Wisdom: " << _subject->getWisdom() << " (+" << _subject->getModWisdom() << ")"<< endl;
		cout << "Constitution: " << _subject->getConstitution() << " (+" << _subject->getModConstitution() << ")" << endl;
		cout << "Armor: " << _subject->getArmorClass() << endl;
		cout << "Attack Damage: " << _subject->getDamageBonus() << endl;
		cout << "Attack Bonus: " << _subject->getAttackBonus() << endl;
		cout << "Current HP: " << _subject->getHitPoints() << endl;
		cout << "================================================================================" << endl;

}
