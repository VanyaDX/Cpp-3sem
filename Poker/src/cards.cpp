#include "include/cards.h"
#include <sstream>

OpenCard::OpenCard() {
    suit = Suit::clubs;
    rank = 0;
}

OpenCard::OpenCard(Suit const x, int const y) {
    suit = x;
    rank = y;
}

int OpenCard::getRank()const {
    return rank;
}


Suit OpenCard::getSuit()const {
    return suit;
}


CloseCard::CloseCard() {}

CloseCard::CloseCard(Suit const x, int const y) {
    suit = x;
    rank = y;
}

bool OpenCard::operator==(OpenCard const &another) {
    return rank == another.getRank() && suit == another.getSuit();
}

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
