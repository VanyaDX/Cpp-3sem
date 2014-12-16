#ifndef _H_PLAYER_MAN_
#define _H_PLAYER_MAN_

#include "player.h"
#include "cards.h"

class player_man: public Player {
private:
public:
    player_man() {}
    player_man(std::string name): Player(name) { }
    ~player_man() {}
    // Player make's bet
    uint32_t bet(uint32_t sum, Table state);
};


#endif
