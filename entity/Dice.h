#pragma once
#ifndef DICE_H
#define DICE_H
namespace d20Logic {
	class Dice
	{
	public:
		Dice();
		int roll_4d6();
		int roll_d8();
		int roll_d10();
		int roll_d20();
	};
}
#endif