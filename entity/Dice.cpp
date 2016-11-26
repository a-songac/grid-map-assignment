#include <cstdlib>
#include <ctime>

#include "Dice.h"

//Default constructor
Dice::Dice()
{
	srand((unsigned)time(0));
}

//Roll a 4d6
int Dice::roll_4d6()
{

	int i = 0, j = 0, indexFound = 0, max = 0;
	int results[4] = { 0, 0, 0, 0 }, sortedResults[4] = { 0, 0, 0, 0 };

	//Roll each die
	for (i = 0; i<4; ++i) {
		results[i] = (rand() % 6) + 1;
	}

	//Sort the results
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; ++j)
		{
			if (results[j] > max) {
				max = results[j];
				indexFound = j;
			}
		}

		results[indexFound] = 0;
		sortedResults[i] = max;
		max = 0;
	}

	//Add first 3 elements
	int sumOfDice = sortedResults[0] + sortedResults[1] + sortedResults[2];

	return sumOfDice;

}

int Dice::roll_d8() {

	return ((rand() % 8) + 1);

}

//Roll a d10
int Dice::roll_d10()
{
	return ((rand() % 10) + 1);
}

int Dice::roll_d20() {

	return ((rand() % 20) + 1);

}
