#include <iostream>
#include <algorithm>
#include <ctime>
#include "include/table.h"
#include "include/holdem_poker.h"
#include "include/player.h"
#include "include/cards.h"
#include "include/player_man.h"
#include "game_help.cpp"

using namespace std;

int main() {
    TextUI* ui = new TextUI(false);
    holdem_poker* poker = newGame((unsigned)2, (unsigned)100, (unsigned) 10, ui,
            new PlayerMan("First player", ui), new PlayerMan("Second player", ui));
    poker->run();
    delete poker;
    return 0;
}
