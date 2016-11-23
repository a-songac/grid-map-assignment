#include "FriendlyPlayerStrategy.h"


void FriendlyPlayerStrategy::move(GamePlayer* player) {
}
void FriendlyPlayerStrategy::attack(GamePlayer* player, GamePlayer* victim) {
}
void FriendlyPlayerStrategy::freeAction(GamePlayer* player) {
}
bool FriendlyPlayerStrategy::turn(GamePlayer* player, Map* map){
    cout << "Friendly took his turn" << endl;
    return true;
}
