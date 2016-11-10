
#include "CharacterView.h"
#include "../entity/Character.h"
#include <iostream>
#include <iomanip>
using namespace std;

CharacterView::CharacterView() {

};

CharacterView::CharacterView(Character* c) {
	//Upon instantiation, attaches itself
	//to a ClockTimer

	_subject = c;
	_subject->attach(this);
};

CharacterView::~CharacterView() {
	_subject->detach(this);
};

void CharacterView::update() {

	display();
};

void CharacterView::display() {


		cout << "================================================================================" << endl;
		cout << "Level: " << _subject->getLevel() << endl;
		cout << "Strength: " << _subject->getStrenght() << " (+" << _subject->getModStrenght() << ")"<< endl;
		cout << "Dexterity: " << _subject->getDexterity() << " (+" << _subject->getModDexterity() << ")"  << endl;
		cout << "Intelligence: " << _subject->getIntelligence() << " (+" << _subject->getModIntelligence() << ")" << endl;
		cout << "Charisma: " << _subject->getCharisma() << " (+" << _subject->getModCharisma() << ")" << endl;
		cout << "Wisdom: " << _subject->getWisdom() << " (+" << _subject->getModWisdom() << ")"<< endl;
		cout << "Constitution: " << _subject->getConstitution() << " (+" << _subject->getModConstitution() << ")" << endl;
		cout << "Armor: " << _subject->getArmor() << endl;
		cout << "Attack Damage: " << _subject->getAttackDamage() << endl;
		cout << "Attack Bonus: " << _subject->getAttackBonus() << endl;
		cout << "Current HP: " << _subject->getHitPoints() << endl;
		cout << "================================================================================" << endl;

}
