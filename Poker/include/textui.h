#ifndef _H_TEXTUI_
#define _H_TEXTUI_
#include "player.h"
#include "cards.h"

class Player;
class OpenCard;

class TextUI
{
public:
    bool noUI;
    TextUI() { noUI = false; }
    TextUI(bool ui);
    void printState(const Player& p, const Table& bs);
    void print(std::string s);
    void raise(Player *p, unsigned to, unsigned bet);
    void call(Player *p, unsigned to, unsigned bet);
    void allIn(Player *p, unsigned total);
    void check(Player *p);
    void fold(Player *p);
    void smallBlind(Player *p, unsigned value);
    void bigBlind(Player *p, unsigned value);
    void showdown(Player *p, OpenCard *cards, unsigned *value);
    void win(std::vector<Player*> winners);
    void gameOver(std::vector<Player*> players, std::vector<unsigned> cash);
    unsigned askForUnsigned(Player *p, unsigned minBet);
};

#endif 
