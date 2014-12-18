#ifndef _H_CARDS_
#define _H_CARDS_

#include "holdem_poker.h"

enum Suit {
    clubs, diamonds, hearts, spades
};

class Card {
protected:
    Suit suit;
    int rank;
public:
    Card() {}
};

class OpenCard: Card {
public:
    // Get Rank
    int getRank()const;
    // Get Suit
    Suit getSuit()const;
    // create open card (to table)
    OpenCard();
    OpenCard(const Suit, const int);
    // required for std::count
    bool operator==(OpenCard const&);
    // returns string description of a card
    std::string toString() const;
};

class CloseCard: Card {
public:
    friend class holdem_poker;
    // create close card (to deck)
    CloseCard();
    CloseCard(const Suit, const int);
};

#endif
