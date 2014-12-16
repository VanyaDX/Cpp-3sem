#ifndef _H_HOLDEM_POKER_
#define _H_HOLDEM_POKER_

#include <vector>

#include "player_man.h"
#include "table.h"
#include "memory.h"

class OpenCard;

class CloseCard;

class Player;

class Table;

class holdem_poker {
private:
    struct PlayerData {
        uint32_t cash;
        OpenCard *hand;
        uint32_t currBet;
        Player *p;


        ~PlayerData();
    } *players;

    uint32_t playersCount, bank, littleBlind, dealer;

    void show(Player *p, OpenCard *cards, uint32_t *value);

    std::string rankToString(uint32_t in);

    // Get id,relevance and kickers of combination
    uint32_t *enter(OpenCard *cards);

    // Get the highest combination
    std::pair<OpenCard *, uint32_t *> strongestCombination(OpenCard *);

    // Get winners
    std::vector<uint32_t> show();

    // Player's betting process
    void doBets(uint32_t pls);

    // New round with i's player
    void doRound();

    // Giving new cards
    void shuffle();

    // Checking if player can acces blind
    std::vector<uint32_t> refresh();

    // Remove card from deck and add to table
    void openNext();

    // Get players who are able to bet
    size_t inGameWithCash();

    // Get state for players[player].p
    Table getTable(uint32_t player, std::vector<uint32_t> live);

    std::vector<OpenCard> table;
    std::vector<CloseCard> deck;

    // Get players in game
    std::vector<uint32_t> live;

    // Creating new player->adding to instance
    template<typename First>
    void addPlayers(uint32_t cnt, First *first);

    template<typename First, typename... Rest>
    void addPlayers(uint32_t cnt, First *first, Rest *... rest);

    holdem_poker();
    template<typename ... Players>
    friend holdem_poker *newGame(uint32_t n, uint32_t startCash, uint32_t littleBlind,
            Players *... p);



public:
    ~holdem_poker();

    void run();
};

#endif
