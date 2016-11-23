#include "AggressivePlayerStrategy.h"


void AggressivePlayerStrategy::move(const GamePlayer* player) {
}
void AggressivePlayerStrategy::attack(const GamePlayer* player, GamePlayer* victim) {
}
void AggressivePlayerStrategy::freeAction(const GamePlayer* player) {
}
bool AggressivePlayerStrategy::turn(const GamePlayer* player, const Map* map){
    cout << "Hostile took his turn" << endl;
    return true;
}
