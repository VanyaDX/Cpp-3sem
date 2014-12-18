#include "include/table.h"
#include <iostream>
#include "include/cards.h"

Table::Table() {
    hand = std::nullptr_t();
}

Table::~Table() {
    if (hand != std::nullptr_t())
        delete[] hand;
}

// prints all info into stdout
void Table::print() const {
    std::cout << "Money on table: " << bank << "\n";
    std::cout << "Your money: " << playerCash << "; Your total bet: " << playerBet << "\n";
    for (uint32_t i = 0; i < enemyCount; i++) {
        std::cout << names[i] << "'s money: " << cash[i] << "; "<<names[i] <<" total bet: " << bets[i] << "\n";
    }
    if (board.size() != 0) {
        std::cout << "On table cards: ";
        for (uint32_t i = 0; i < board.size(); i++) {
            std::cout << board[i].toString() << " ";
        }
        std::cout << "\n";
    }
    std::cout << "On hand cards: " << hand[0].toString() << " " << hand[1].toString() << "\n";
}
