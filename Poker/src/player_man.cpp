#include <iostream>
#include <string>
#include <sstream>
#include "include/player_man.h"

using namespace std;

uint32_t player_man::bet(uint32_t sum, Table state) {
    std::cout << "[" << this->getName() << "] Your sum to bet \n min bet -> " << sum << "\n 0 it's check or fold: \n";
    std::string s;
    std::getline(std::cin, s);
    std::stringstream ss;
        ss << s;
        unsigned long as;
        ss >> as;
    return as;
}
