#include "include/cards.h"
#include <sstream>

//create open card (to table)
OpenCard::OpenCard() {
    suit = Suit::clubs;
    rank = 0;
}

OpenCard::OpenCard(Suit const x, int const y) {
    suit = x;
    rank = y;
}

//return Rank of open card
int OpenCard::getRank()const {
    return rank;
}

//return Suit of open card
Suit OpenCard::getSuit()const {
    return suit;
}

//create close card
CloseCard::CloseCard() {}

CloseCard::CloseCard(Suit const x, int const y) {
    suit = x;
    rank = y;
}

// required for std::count
bool OpenCard::operator==(OpenCard const &another) {
    return rank == another.getRank() && suit == another.getSuit();
}

// returns string description of a card
std::string OpenCard::toString() const {
    std::string rankStr;
    switch (rank) {
        case 11:
            rankStr = "J";
            break;
        case 12:
            rankStr = "Q";
            break;
        case 13:
            rankStr = "K";
            break;
        case 14:
            rankStr = "A";
            break;
        default:
        {
            std::stringstream ss;
            std::string s;
            ss << rank;
            s = ss.str();
            rankStr =s;
            break;
        }
    }
    std::string suitChars[] = {"♠ ", "♦ ", "♥ ", "♣ "};
    return (rankStr + suitChars[(int) suit]);
}
