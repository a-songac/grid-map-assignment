#include "UserPlayerStrategy.h"


void UserPlayerStrategy::move(const GamePlayer* player) {
}
void UserPlayerStrategy::attack(const GamePlayer* player, GamePlayer* victim) {
}
void UserPlayerStrategy::freeAction(const GamePlayer* player) {
}
bool UserPlayerStrategy::turn(const GamePlayer* player, const Map* map){
    cout << "User took his turn" << endl;
    return true;
}
