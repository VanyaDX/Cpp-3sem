#include <algorithm>
#include <ctime>

#include "include/holdem_poker.h"
#include "include/cards.h"

template <class ... Players>
holdem_poker* newGame(uint32_t n, uint32_t startCash, uint32_t littleBlind, TextUI* ui, Players* ... p) {
    holdem_poker* res = new holdem_poker();
    res->UI = ui;
    res->playersCount = n;
    res->littleBlind = littleBlind;
    res->deck = std::vector <CloseCard>();
    res->table = std::vector <OpenCard>();

    res->players = new holdem_poker::PlayerData[res->playersCount];
    res->addPlayers(0, p...);

    for (uint32_t i = 0; i < res->playersCount; i++) {
        res->players[i].cash = startCash;
        res->players[i].hand = new OpenCard[2];
    }
    res->shuffle();

    return res;
}

template <typename Player>
void holdem_poker::addPlayers(unsigned cnt, Player* p) {
    if (cnt < playersCount) {
        players[cnt].p = p;
    }
}

template <typename Player, typename... Team>
void holdem_poker::addPlayers(unsigned cnt, Player* p, Team* ... t) {
    if (cnt < playersCount) {
        players[cnt].p = p;
        addPlayers(++cnt, t...);
    }
}
