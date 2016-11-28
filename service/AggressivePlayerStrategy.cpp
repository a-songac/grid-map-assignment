#include "AggressivePlayerStrategy.h"

#include "CombatService.h"



void AggressivePlayerStrategy::attack(GamePlayer* player, GamePlayer* victim, bool melee) {
    CombatService::attack(player->getInGameCharacter(), victim->getInGameCharacter(), melee);
}
void AggressivePlayerStrategy::freeAction(GamePlayer* player) {
}

