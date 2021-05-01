#include "Virologist.hpp"

using namespace std;
using namespace pandemic;

Player& Virologist::treat(City c){
    if (city != c) {
        if(cards.find(c)==cards.end()) {
            throw std::invalid_argument{"illegal action: you have no card of city " + city_string(c)};
        }
        cards.erase(c);
    }
    else if (board[c] == 0) {
        throw std::invalid_argument{"illegal action: no more cubes remain in city " + city_string(c)};
    }
    else if (board.is_cure_discoverd(c)) {
        board[c] = 0;
    }
    else {
        board[c]--;
    }
    // std::cout << "Treat city " << city_string(c) << " to " << board[c] << std::endl;
    return *this;
}