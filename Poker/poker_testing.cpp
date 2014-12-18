#include <fstream>
#include <time.h>
#include <stdlib.h>

#include "gtest/gtest.h"
#include "include/holdem_poker.h"
#include "game_help.cpp"
#include "include/player_man.h"
#include "include/textui.h"

namespace {
    const int N = 1000;
    const char *evaluateFile = "evaluateCards.txt",
               *chooseFile = "chooseCards.txt";

    // read m pairs of two numbers (cards) from file
    // 0 is clubs, 1 is diamonds, 2 is hearts and 3 is spades
    // m is the first number in file
    std::pair<size_t, OpenCard*> readCards(const char* path) {
        std::ifstream fin(path);
        int m, rank, s;
        fin >> m;
        OpenCard* out = new OpenCard[m];
        for (int i = 0; i < m; i++) {
            fin >> rank >> s;
            out[i] = OpenCard((Suit)s, rank);
        }

        return std::make_pair(m, out);
    }

    // returns:
    //     -1: a < b
    //     0: a == b
    //     1: a > b
    int unsigned7cmp (unsigned* a, unsigned* b) {
        for (int i = 0; i < 7; i++) {
            if (a[i] != b[i]) {
                return - (a[i] < b[i]) + (a[i] > b[i]);
            }
        }
        return 0;
    }
}

TEST(correctness, constructor) {
    TextUI* ui = new TextUI(true);
    holdem_poker* game = newGame((unsigned)2, (unsigned)100, (unsigned) 10, ui,
            new PlayerMan("First player", ui), new PlayerMan("Second player", ui));
    delete game;
}

TEST(correctness, shuffleTest) {
    TextUI* ui = new TextUI(true);
    holdem_poker* game = newGame((unsigned)2, (unsigned)100, (unsigned) 10, ui,
            new PlayerMan("First player", ui), new PlayerMan("Second player", ui));
    OpenCard cards[9];
    for (int i = 0; i < N; i++) {
        game->shuffle();
        for (int j = 0; j < 5; j++) {
            game->openNext();
            cards[j] = game->table.back();
        }
        cards[5] = game->players[0].hand[0];
        cards[6] = game->players[0].hand[1];
        cards[7] = game->players[1].hand[0];
        cards[8] = game->players[1].hand[1];

        for (int j = 0; j < 9; j++) {
            EXPECT_TRUE(cards[j].getRank() >= 2);
            EXPECT_TRUE(cards[j].getRank() <= 14);
            EXPECT_TRUE((int)cards[j].getSuit() <= 4);
            EXPECT_EQ(1, std::count(cards, cards + 9, cards[j]));
        }
    }
    delete game;
}

// Combinations compare to each over, order has to be equal to following:
// (less first)
TEST(correctness, evaluateCombination) {
    TextUI* ui = new TextUI(true);
    holdem_poker* game = newGame((unsigned)2, (unsigned)100, (unsigned) 10, ui,
            new PlayerMan("First player", ui), new PlayerMan("Second player", ui));
    std::pair<size_t, OpenCard*> out = readCards(evaluateFile);
    OpenCard *testCards = out.second;

    srand (time(NULL));
    for (size_t i = 0; i < out.first / 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::swap(testCards[5 * i + j], testCards[5 * i + rand() % 5]);
        }
    }

    unsigned *valueI, *valueJ;
    for (size_t i = 0; i < out.first / 5; i++) {
        valueI = game->enter(&testCards[5 * i]);
        for (size_t j = 0; j < out.first / 5; j++) {
            valueJ = game->enter(&testCards[5 * j]);
            if (i != j) {
                EXPECT_EQ(i < j ? -1 : 1, unsigned7cmp(valueI, valueJ));
                if ((i < j ? -1 : 1) != unsigned7cmp(valueI, valueJ)) {
                    std::cout << i << " " << j << "\n";
                }
            }
            else {
                EXPECT_EQ(0, unsigned7cmp(valueI, valueJ));
            }
            delete[] valueJ;
        }
        delete[] valueI;
    }

    delete[] testCards;
    delete game;
}

// highestComb should pick first five cards of 7 cards combination:
TEST(correctness, pickCombination) {
    TextUI* ui = new TextUI(true);
    holdem_poker* game = newGame((unsigned)2, (unsigned)100, (unsigned) 10, ui,
            new PlayerMan("First player", ui), new PlayerMan("Second player", ui));
    std::pair<size_t, OpenCard*> out = readCards(chooseFile);
    OpenCard *testCards = out.second;
    OpenCard *shuffledCards = new OpenCard[out.first];
    memcpy(shuffledCards, out.second, out.first * sizeof(OpenCard));

    srand (time(NULL));
    for (size_t i = 0; i < out.first / 7; i++) {
        for (int j = 0; j < 7; j++) {
            std::swap(shuffledCards[7 * i + j], shuffledCards[7 * i + rand() % 7]);
        }
    }

    for (unsigned i = 0; i < out.first / 7; i++) {
        std::pair<OpenCard*, unsigned*> result = game->strongestCombination(&shuffledCards[i * 7]);
        for (unsigned j = 0; j < 5; j++) {
            if (std::count(testCards + i * 7, testCards + i * 7 + 5, result.first[j]) != 1) {
                int x;
                x++;
            }
            EXPECT_EQ(5, std::count(testCards + i * 7, testCards + i * 7 + 5, result.first[j]));
        }
        delete[] result.first;
        delete[] result.second;
    }

    delete[] testCards;
    delete[] shuffledCards;
    delete game;
}
