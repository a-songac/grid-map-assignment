#pragma once

#include "../core/Observer.h"
#include "../entity/Character.h"

class CharacterView : public Observer {

public:
	CharacterView();
	CharacterView(Character*);
	~CharacterView();
	void update();
	void display();


private:
	Character* _subject;
};
