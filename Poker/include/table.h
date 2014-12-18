#ifndef _H_TABLE_
#define _H_TABLE_

#include "cards.h"

class OpenCard;

struct Table {
    uint32_t enemyCount, bank, littleBlind, playerCash, playerBet;
    OpenCard *hand;
    std::vector <OpenCard> board;
    std::vector <std::string> names;
    std::vector <uint32_t> cash, bets;
    Table();
    ~Table();
    // prints all info into stdout
    void print() const;
};

#endif
