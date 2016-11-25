#pragma once

#include "utils\LogUtils.h"
#include "entity\Dice.h"
#include "entity\Character.h"

class Combat
{
public:
	Combat();
	bool Collide(Character Theplayer, Character TheEnemy);
	~Combat();
};

