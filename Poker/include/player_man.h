#ifndef _H_PLAYER_MAN_
#define _H_PLAYER_MAN_

#include "player.h"
#include "cards.h"
#include "textui.h"

class PlayerMan: public Player {
private:
    TextUI* UI;
public:
    PlayerMan() {};
    PlayerMan(std::string name, TextUI *ui): Player(name) { UI = ui; }
    ~PlayerMan() {};
    // print state & ask user for action
    // throws std::invalid_argument, std::out_of_range in case of incorrect input
    uint32_t bet(uint32_t sum, Table state);
};


#endif
