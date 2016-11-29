#include "AggressivePlayerStrategy.h"

#include "CombatService.h"



void AggressivePlayerStrategy::attack(GamePlayer* player, GamePlayer* victim, bool melee) {
    CombatService::attack(player->getInGameCharacter(), victim->getInGameCharacter(), melee);
    cout << "After attack from opponent, you end up with " << victim->getInGameCharacter()->getHitPoints() << " HP." << endl;
        readStringInput("Press any key to continue...", "");
}
void AggressivePlayerStrategy::freeAction(GamePlayer* player) {
}

