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
