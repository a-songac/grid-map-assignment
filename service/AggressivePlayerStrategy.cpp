#include "AggressivePlayerStrategy.h"


void AggressivePlayerStrategy::move(GamePlayer* player) {
}
void AggressivePlayerStrategy::attack(GamePlayer* player, GamePlayer* victim) {
}
void AggressivePlayerStrategy::freeAction(GamePlayer* player) {
}
bool AggressivePlayerStrategy::turn(GamePlayer* player, Map* map){
    cout << "Hostile took his turn" << endl;
    return true;
}
