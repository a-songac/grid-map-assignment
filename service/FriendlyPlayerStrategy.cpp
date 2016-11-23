#include "FriendlyPlayerStrategy.h"


void FriendlyPlayerStrategy::move(const GamePlayer* player) {
}
void FriendlyPlayerStrategy::attack(const GamePlayer* player, GamePlayer* victim) {
}
void FriendlyPlayerStrategy::freeAction(const GamePlayer* player) {
}
bool FriendlyPlayerStrategy::turn(const GamePlayer* player, const Map* map){
    cout << "Friendly took his turn" << endl;
    return true;
}
