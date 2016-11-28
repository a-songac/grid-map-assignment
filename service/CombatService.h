/// @file
/// @brief
/// Header file for CombatService.class
///
/// @details
/// 1. Game Rules: Combat Service executes the combat attack based on d20 rules. The following sequence of execution is used: \n
///     a) Attacker rolls d20 dice to obtain attack attempt value
///     b) add attacker's attack modifier to attack attemp value
///     c) add attacker's weapon modifier to attack attempt value (stregth if melee attack, dexterity if range attack)
///     d) if total attack attempt value is greater than opponent's armor class value, the attack is successful
///         i) In case of successful attack, compute damage to inflict
///         ii) roll d8 dice
///         iii) add damage modifier to roll value
///         iv) the total value is deducted from opponent's HP \n\n
/// 2. Design: The CombatService is used as a static class (provides static methods only). \n\n
/// 3. Libraries: Standard libraries: <sstream> <vector> <string>


#pragma once

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "../entity/Coordinate.h"
#include "../entity/Character.h"
#include "../entity/GamePlayer.h"
#include "ShortestPath.h"

class CombatService {
    public:
        static bool isAdjacent(Coordinate origin, Coordinate destination);
        static bool canRangeAttack(Coordinate origin, Coordinate destination, int range, Map* map);
        static bool attack(Character* attacker, Character* victim, bool melee);
        static void eliminateDeadBodies(Map* map);

};
