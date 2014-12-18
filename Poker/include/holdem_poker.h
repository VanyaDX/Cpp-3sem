#ifndef _H_HOLDEM_POKER_
#define _H_HOLDEM_POKER_

#include <vector>
#include "gtest/gtest.h"
#include "cards.h"
#include "player.h"
#include "table.h"
#include "memory.h"
#include "textui.h"


class OpenCard;

class CloseCard;

class Player;

class Table;

class TextUI;

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

    //void show(Player *p, OpenCard *cards, uint32_t *value);

    //std::string rankToString(uint32_t in);

    // Get id,relevance and kickers of combination
    uint32_t *enter(OpenCard *cards);

    // Get the highest combination
    std::pair<OpenCard *, uint32_t *> strongestCombination(OpenCard *);

    // Get vector with winnerses ids
    std::vector<uint32_t> show();

    // Player's betting process
    void doBets(uint32_t pls);

    // New round with i's player
    void doRound();

    // Giving new cards to players & deck
    void shuffle();

    // Checking if player can acces blind
    std::vector<uint32_t> refresh();

    // Remove card from deck and add to table
    void openNext();

    // Get players who are able to bet
    size_t inGameWithCash();

    // Get state for players[player].p
    Table getTable(uint32_t player, std::vector<uint32_t> live);
    //cards on table
    std::vector<OpenCard> table;
    //deck of cards
    std::vector<CloseCard> deck;

    // Get players in game
    std::vector<uint32_t> live;

    // Creating new player->adding to instance
    template<typename First>
    void addPlayers(uint32_t cnt, First *first);
    template<typename First, typename... Rest>
    void addPlayers(uint32_t cnt, First *first, Rest *... rest);

    holdem_poker();
    // Permits static function is not a class to create an object without a template in it
    // Should be used instead of the default constructor
    template<typename ... Players>
    friend holdem_poker *newGame(uint32_t n, uint32_t startCash, uint32_t littleBlind,
                                 TextUI* ui, Players *... p);
    TextUI* UI;

    //need for testing
    FRIEND_TEST(correctness, evaluateCombination);
    FRIEND_TEST(correctness, pickCombination);
    FRIEND_TEST(correctness, shuffleTest);

public:
    ~holdem_poker();
	
    //running until there is no winner
    void run();
};

#endif
