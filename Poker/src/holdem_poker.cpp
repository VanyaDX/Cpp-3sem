#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iostream>
#include <time.h>
#include <string.h>
#include <vector>
#include <sstream>



#include "include/holdem_poker.h"
#include "include/table.h"
#include "include/cards.h"

using namespace std;

namespace {

    bool comparatorByRank(const OpenCard &a, const OpenCard &b) {
        return a.getRank() > b.getRank();
    }

    bool comparatorBySuit(const OpenCard &a, const OpenCard &b) {
        return (int) a.getSuit() == (int) b.getSuit() ? a.getRank() < b.getRank() : (int) a.getSuit() < (int) b.getSuit();
    }
}

holdem_poker::holdem_poker() {
}

uint32_t *holdem_poker::enter(OpenCard *cards) {
    uint32_t *res = new uint32_t[7];
    for (int i = 0; i < 7; i++) {
        res[i] = 0;
    }

    std::sort(cards, cards + 5, comparatorBySuit);
    if (cards[0].getSuit() == cards[4].getSuit()) {
        res[0] = 5;
        res[1] = (uint32_t) cards[4].getRank();;
        res[2] = (uint32_t) cards[4].getRank();
        res[3] = (uint32_t) cards[3].getRank();
        res[4] = (uint32_t) cards[2].getRank();
        res[5] = (uint32_t) cards[1].getRank();
        res[6] = (uint32_t) cards[0].getRank();
    }

    std::sort(cards, cards + 5, comparatorByRank);
    int diff[4], pos = 0;
    for (int i = 0; i < 4; i++) {
        if (cards[i].getRank() - cards[i + 1].getRank() > 1)
            pos = i + 1;
        diff[i] = cards[i].getRank() - cards[i + 1].getRank();
    }

    bool straight = true;
    for (int i = pos; i < pos + 4; i++) {
        if ((i + 1) % 5 == 0 ? (cards[4].getRank() != 2 || cards[0].getRank() != 14) && pos != 0 : cards[i % 5].getRank() - cards[(i + 1) % 5].getRank() != 1)
            straight = false;
    }

    if (straight) {
        res[1] = (uint32_t) cards[std::max(pos - 1, 0)].getRank();
        res[0] = res[0] == 5 ? cards[0].getRank() == 14 && cards[4].getRank() == 10 ? 9 : 8 : 4;
    }

    uint32_t code = 0;
    for (int i = 0; i < 4; i++) {
        code |= (1 << i) * (diff[3 - i] != 0);
    }

    if (code == 1 && res[0] < 7) {
        res[0] = 7;
        res[1] = (uint32_t) cards[0].getRank();
        res[2] = (uint32_t) cards[4].getRank();
    }
    else if (code == 8 && res[0] < 7) {
        res[0] = 7;
        res[1] = (uint32_t) cards[1].getRank();
        res[2] = (uint32_t) cards[0].getRank();
    }

    else if (code == 2 && res[0] < 6) {
        res[0] = 6;
        res[1] = (uint32_t) cards[0].getRank() * 14 + cards[3].getRank();
    }
    else if (code == 4 && res[0] < 6) {
        res[0] = 6;
        res[1] = (uint32_t) cards[3].getRank() * 14 + cards[0].getRank();
    }

    else if (code == 3 && res[0] < 3) {
        res[0] = 3;
        res[1] = (uint32_t) cards[0].getRank();
        res[2] = (uint32_t) cards[3].getRank();
        res[3] = (uint32_t) cards[4].getRank();
    }
    else if (code == 9 && res[0] < 3) {
        res[0] = 3;
        res[1] = (uint32_t) cards[1].getRank();
        res[2] = (uint32_t) cards[0].getRank();
        res[3] = (uint32_t) cards[4].getRank();
    }
    else if (code == 12 && res[0] < 3) {
        res[0] = 3;
        res[1] = (uint32_t) cards[2].getRank();
        res[2] = (uint32_t) cards[0].getRank();
        res[3] = (uint32_t) cards[1].getRank();
    }

    else if (code == 5 && res[0] < 2) {
        res[0] = 2;
        res[1] = (uint32_t) std::max(cards[0].getRank(), cards[2].getRank()) * 14 +
                std::min(cards[0].getRank(), cards[2].getRank());
        res[2] = (uint32_t) cards[4].getRank();
    }
    else if (code == 6 && res[0] < 2) {
        res[0] = 2;
        res[1] = (uint32_t) std::max(cards[0].getRank(), cards[3].getRank()) * 14 +
                std::min(cards[0].getRank(), cards[3].getRank());
        res[2] = (uint32_t) cards[2].getRank();
    }
    else if (code == 10 && res[0] < 2) {
        res[0] = 2;
        res[1] = (uint32_t) std::max(cards[1].getRank(), cards[3].getRank()) * 14 +
                std::min(cards[1].getRank(), cards[3].getRank());
        res[2] = (uint32_t) cards[0].getRank();
    }

    else if (code == 7 && res[0] < 1) {
        res[0] = 1;
        res[1] = (uint32_t) cards[0].getRank();
        res[2] = (uint32_t) cards[2].getRank();
        res[3] = (uint32_t) cards[3].getRank();
        res[4] = (uint32_t) cards[4].getRank();
    }
    else if (code == 11 && res[0] < 1) {
        res[0] = 1;
        res[1] = (uint32_t) cards[1].getRank();
        res[2] = (uint32_t) cards[0].getRank();
        res[3] = (uint32_t) cards[3].getRank();
        res[4] = (uint32_t) cards[4].getRank();
    }
    else if (code == 13 && res[0] < 1) {
        res[0] = 1;
        res[1] = (uint32_t) cards[2].getRank();
        res[2] = (uint32_t) cards[0].getRank();
        res[3] = (uint32_t) cards[1].getRank();
        res[4] = (uint32_t) cards[4].getRank();
    }
    else if (code == 14 && res[0] < 1) {
        res[0] = 1;
        res[1] = (uint32_t) cards[3].getRank();
        res[2] = (uint32_t) cards[0].getRank();
        res[3] = (uint32_t) cards[1].getRank();
        res[4] = (uint32_t) cards[2].getRank();
    }
    else if (res[0] == 0) {
        res[1] = 0;
        for (int i = 0; i < 5; i++)
            res[1 + i] = (uint32_t) cards[i].getRank();
    }

    return res;
}

holdem_poker::~holdem_poker() {
    delete[] players;
}

holdem_poker::PlayerData::~PlayerData() {
    delete[] hand;
    delete p;
}

namespace {
    bool nextCombination(size_t *item, size_t n, size_t N) {
        for (size_t i = 1; i <= n; ++i) {
            if (item[n - i] < N - i) {
                ++item[n - i];
                for (size_t j = n - i + 1; j < n; ++j) {
                    item[j] = item[j - 1] + 1;
                }
                return true;
            }
        }
        return false;
    }
    int compInts(uint32_t *a, uint32_t *b) {
        for (int i = 0; i < 7; i++) {
            if (a[i] != b[i]) {
                return -(a[i] < b[i]) + (a[i] > b[i]);
            }
        }
        return 0;
    }
}


std::pair<OpenCard *, uint32_t *> holdem_poker::strongestCombination(OpenCard *source) {
    size_t cardIndex[5], n = 7, k = 5;
    for (size_t i = 0; i < k; i++) {
        cardIndex[i] = i;
    }
    uint32_t *currValue, *maxValue = new uint32_t[7];
    memset(maxValue, 0, sizeof(uint32_t) * 7);
    OpenCard *curr = new OpenCard[k], *maxCard = new OpenCard[k];
    do {
        for (size_t i = 0; i < k; i++) {
            curr[i] = source[cardIndex[i]];
        }
        currValue = enter(curr);
        if (compInts(currValue, maxValue) == 1) {
            memcpy(maxValue, currValue, sizeof(uint32_t) * 7);
            memcpy(maxCard, curr, sizeof(OpenCard) * k);
        }
        delete[] currValue;
    } while (nextCombination(cardIndex, k, n));
    delete[] curr;

    return std::make_pair(maxCard, maxValue);
}

std::vector<uint32_t> holdem_poker::refresh() {
    std::vector<uint32_t> res;
    for (uint32_t i = 0; i < playersCount; i++) {
        if (players[i].cash != 0)
            res.push_back((uint32_t const &) i);
    }
    return res;
}

void holdem_poker::doRound() {
    std::cout << "Game started\n";
    table.clear();
    uint32_t small = std::count(live.begin(), live.end(), (dealer + 1) % playersCount) ? (dealer + 1) % playersCount : std::upper_bound(live.begin(), live.end(), (dealer + 1) % playersCount) == live.end() ? live[0] : *std::upper_bound(live.begin(), live.end(), (dealer + 1) % playersCount);
    uint32_t big = std::count(live.begin(), live.end(), (small + 1) % playersCount) ? (small + 1) % playersCount : std::upper_bound(live.begin(), live.end(), (small + 1) % playersCount) == live.end() ? live[0] : *std::upper_bound(live.begin(), live.end(), (small + 1) % playersCount);
    players[small].cash -= std::min(littleBlind, players[small].cash);
    players[small].currBet = std::min(littleBlind, players[small].cash);
    std::cout << players[small].p->getName() << " did little blind: adds " << std::min(littleBlind, players[small].cash) << std::endl;
    players[big].cash -= std::min(littleBlind * 2, players[big].cash);
    players[big].currBet = std::min(littleBlind * 2, players[big].cash);
    std::cout << players[big].p->getName() << " did big blind: adds " << std::min(littleBlind * 2, players[big].cash) << std::endl;
    bank = std::min(littleBlind, players[small].cash) + std::min(littleBlind * 2, players[big].cash);
    uint32_t plg = big = std::count(live.begin(), live.end(), (big + 1) % playersCount) ? (big + 1) % playersCount : std::upper_bound(live.begin(), live.end(), (big + 1) % playersCount) == live.end() ? live[0] : *std::upper_bound(live.begin(), live.end(), (big + 1) % playersCount);
    doBets(plg);
    for (int i = 0; i < 3; i++)
        openNext();
    if (inGameWithCash() > 1)
        doBets(plg);
    openNext();
    if (inGameWithCash() > 1)
        doBets(plg);
    openNext();
    if (inGameWithCash() > 1)
        doBets(plg);
    std::vector<uint32_t> winners = show();
    assert(winners.size() > 0);
    std::vector<Player *> winnersPointers;
    for (uint32_t i = 0; i < winners.size(); i++) {
        players[winners[i]].cash += bank / winners.size();
        winnersPointers.push_back(players[winners[i]].p);
    }
    if (winnersPointers.size() == 1) {
        std::cout << "Winner:";
    }
    else {
        std::cout << "Winners:";
    }
    for (auto it = winnersPointers.begin(); it != winnersPointers.end(); it++) {
        std::cout << " " << (*it)->getName();
    }
    std::cout << "\n";
}

void holdem_poker::doBets(uint32_t pls) {
    uint32_t last = pls, curr = last, value, currBet = 0;
    for (uint32_t i = 0; i < live.size(); i++) {
        currBet = std::max(currBet, players[live[i]].currBet);
    }

    do {
        if (players[curr].cash != 0) {
            std::cout << "<<" << (*players[curr].p).getName() << ">>\n";
            getTable(curr, live).print();
            for (int i = 0; i < 3; i++) {
                bool wrongInput = false;
                try {
                    value = players[curr].p->bet(currBet - players[curr].currBet, getTable(curr, live));
                }
                catch (...) {
                    wrongInput = true;
                }
                // bet/raise or check/fold or all-in
                if (((players[curr].cash >= value && value + players[curr].currBet >= currBet) || value == 0 ||
                        value == players[curr].cash) && !wrongInput)
                    break;
                if (i == 2) {
                    value = 0;
                    std::cout << "You're only allowed check or fold\n";
                    break;
                }
                else
                    std::cout << "Input another sum ("  << 2 - i << ")\n";
            }
            if (value > 0) {
                if (value + players[curr].currBet > currBet) {
                    last = curr;
                    currBet = value + players[curr].currBet;
                    if (value == players[curr].cash)
                        std::cout << players[curr].p->getName() << " goes all-in: " << currBet << std::endl;
                    else
                        std::cout << players[curr].p->getName() << " raises total bet to " << currBet << ": adds " << value << std::endl;
                }
                else {
                    if (value == players[curr].cash)
                        std::cout << players[curr].p->getName() << " goes all-in: " << players[curr].currBet + value << std::endl;
                    else
                        std::cout << players[curr].p->getName() << " calls total bet to " << currBet << ": adds " << value << std::endl;
                }
                players[curr].cash -= value;
                players[curr].currBet += value;
                bank += value;
            }
            else {
                if (currBet - players[curr].currBet == 0) {
                    std::cout << players[curr].p->getName() << " checks" << std::endl;
                }
                else {
                    std::cout << players[curr].p->getName() << " folds" << std::endl;
                    assert(std::find(live.begin(), live.end(), curr) != live.end());
                    live.erase(std::find(live.begin(), live.end(), curr));
                    if (live.size() == 1)
                        return;
                }
            }
        }
        curr = std::count(live.begin(), live.end(), (curr + 1) % playersCount) ? (curr + 1) % playersCount : std::upper_bound(live.begin(), live.end(), (curr + 1) % playersCount) == live.end() ? live[0] : *std::upper_bound(live.begin(), live.end(), (curr + 1) % playersCount);
    } while (curr != last);
}

std::string holdem_poker::rankToString(uint32_t in) {
    switch (in) {
        case 14:
            return "A";
        case 13:
            return "K";
        case 12:
            return "Q";
        case 11:
            return "J";
        default:
        {
            std::stringstream ss;
            std::string s;
            ss << in;
            s = ss.str();
            return s;
        }
    }
}


void holdem_poker::show(Player *p, OpenCard *cards, uint32_t *value) {
    std::cout << p->getName() << " has ";
    switch (value[0]) {
        case 8:
            if (value[1] == 14) {
                std::cout << "royal flush";
            }
            else {
                std::cout << "straight flush with " << rankToString(value[1]) << " highest";
            }
            break;
        case 7:
            std::cout << "four of a kind of " << rankToString(value[1]) << " and " << rankToString(value[2]) << " kicker";
            break;
        case 6:
            std::cout << "full house with " << rankToString(value[1] / 14) << " and " << rankToString(value[1] % 14) << " highest";
            break;
        case 5:
            std::cout << "flush with " << rankToString(value[1]) << " highest";
            break;
        case 4:
            std::cout << "straight with " << rankToString(value[1]) << " highest";
            break;
        case 3:
            std::cout << "triple of " << rankToString(value[1]) << " and " <<
                    rankToString(value[2]) << ", " << rankToString(value[3]) << "kickers";
            break;
        case 2:
            std::cout << "two pairs: " << rankToString(value[1] / 14) << " and " << rankToString(value[1] % 14) << "; " <<
                    rankToString(value[2]) << " kicker";
            break;
        case 1:
            std::cout << "pair of " << rankToString(value[1]) << " with " << rankToString(value[2]) << ", " << rankToString(value[3]) <<
                    ", " << rankToString(value[4]) << " kickers";
            break;
        case 0:
            std::cout << rankToString(value[1]) << " highest card with " << rankToString(value[2]) << ", " << rankToString(value[3]) << ", " <<
                    rankToString(value[4]) << ", " << rankToString(value[5]) << " kickers";
            break;
        default:
            break;
    }

    std::cout << " (combination:";
    for (int i = 0; i < 5; i++)
        std::cout << " " << cards[i].toString();
    std::cout << ")\n";
}


std::vector<uint32_t> holdem_poker::show() {
    std::vector<uint32_t> winners;
    uint32_t *maxValue = new uint32_t[7];
    memset(maxValue, 0, sizeof(uint32_t) * 7);
    OpenCard currCards[7];
    assert(table.size() == 5);
    for (int j = 0; j < 5; j++) {
        currCards[j] = table[j];
    }
    for (uint32_t i = 0; i < live.size(); i++) {
        currCards[5] = players[live[i]].hand[0];
        currCards[6] = players[live[i]].hand[1];
        std::pair<OpenCard *, uint32_t *> curr = strongestCombination(currCards);
        switch (compInts(curr.second, maxValue)) {
            case 1:
                winners.clear();
                winners.push_back(live[i]);
                memcpy(maxValue, curr.second, 7 * sizeof(uint32_t));
                break;
            case 0:
                winners.push_back(live[i]);
                break;
            default:
                break;
        }

        if (live.size() > 1)
            show(players[live[i]].p, curr.first, curr.second);
        delete[] curr.first;
        delete[] curr.second;
    }
    delete[] maxValue;

    return winners;
}

void holdem_poker::shuffle() {
    std::cout << "Shuffling cards.. \n\n";
    const int N = 52;
    std::pair<Suit, int> deckTmp[N];
    for (int i = 2; i <= 14; i++) {
        for (int j = Suit::clubs; j <= Suit::spades; j++) {
            deckTmp[(i - 2) * 4 + j] = std::make_pair((Suit) j, i);
        }
    }

    std::srand((uint32_t) (time(0)));
    std::random_shuffle(deckTmp, deckTmp + N);
    for (uint32_t i = 0; i < playersCount; i++) {
        players[i].hand[0] = OpenCard(deckTmp[i * 2].first, deckTmp[i * 2].second);
        players[i].hand[1] = OpenCard(deckTmp[i * 2 + 1].first, deckTmp[i * 2 + 1].second);
    }

    for (uint32_t i = playersCount * 2; i < playersCount * 2 + 5; i++) {
        deck.push_back(CloseCard(deckTmp[i * 2].first, deckTmp[i * 2].second));
    }
}

void holdem_poker::openNext() {
    CloseCard chosen = deck.back();
    deck.erase(--deck.end());
    table.push_back(OpenCard(chosen.suit, chosen.rank));
}

Table holdem_poker::getTable(uint32_t player, std::vector<uint32_t> live) {
    int isActive = std::count(live.begin(), live.end(), player);

    Table bs;
    bs.enemyCount = (uint32_t) (live.size() - isActive);
    bs.bank = bank;
    bs.littleBlind = littleBlind;
    bs.playerBet = players[player].currBet;
    bs.playerCash = players[player].cash;
    for (uint32_t i = 0; i < live.size(); i++) {
        if (live[i] != player) {
            bs.bets.push_back(players[live[i]].currBet);
            bs.cash.push_back(players[live[i]].cash);
            bs.names.push_back(players[live[i]].p->getName());
        }
    }
    bs.hand = new OpenCard[2];
    memcpy(bs.hand, players[player].hand, sizeof(OpenCard) * 2);
    bs.board = table;

    return bs;
}

size_t holdem_poker::inGameWithCash() {
    size_t cnt = 0;
    for (uint32_t i = 0; i < live.size(); i++) {
        cnt += (players[live[i]].cash != 0);
    }
    return cnt;
}

void holdem_poker::run() {
    live = refresh();
    dealer = 0;
    bank = 0;

    while (live.size() > 1) {
        shuffle();
        doRound();
        bank = 0;
        live = refresh();
    }

    std::vector<Player *> pl;
    std::vector<uint32_t> c;
    for (uint32_t i = 0; i < playersCount; i++) {
        pl.push_back(players[i].p);
        c.push_back(players[i].cash);
    }
    std::cout << "\nGame over\n";
    for (uint32_t i = 0; i < pl.size(); i++) {
        std::cout << pl[i]->getName() << " has " << c[i] << std::endl;
    }
}
