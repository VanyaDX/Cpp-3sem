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
    
    OpenCard();

    OpenCard(const Suit, const int);

    bool operator==(OpenCard const&);
    // Card to String
    std::string toString() const;
};

class CloseCard: Card {
public:
    friend class holdem_poker;
    CloseCard();
    CloseCard(const Suit, const int);
};

#endif
