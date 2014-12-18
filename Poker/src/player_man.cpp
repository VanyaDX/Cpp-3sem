#include <iostream>

#include "include/player_man.h"
#include "include/textui.h"

// print state & ask user for action
// throws std::invalid_argument, std::out_of_range in case of incorrect input
uint32_t PlayerMan::bet(uint32_t sum, Table state) {
       return UI->askForUnsigned(this, sum);
}
