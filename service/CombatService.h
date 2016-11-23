#pragma once

#include "../entity/Map.h"
#include "../entity/Cell.h"
#include "../entity/Coordinate.h"
#include "../entity/Character.h"
#include "../entity/GamePlayer.h"
#include "ShortestPath.h"

class CombatService {
    public:
        bool canAttack(GamePlayer* player, Mmap* map, bool fromDistance);

}
