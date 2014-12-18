#ifndef _H_PLAYER_
#define _H_PLAYER_

#include <string>

#include "holdem_poker.h"
#include "table.h"

class Table;

class Player {
private:
    std::string name;
public:
    Player() {};
    Player(std::string n) { name = n; }
    // Get Player's name
    std::string getName() const { return name; }
    virtual ~Player() {};
    // Get player's bet or zero
    virtual uint32_t bet(uint32_t sum, Table state) = 0;
};

#endif
