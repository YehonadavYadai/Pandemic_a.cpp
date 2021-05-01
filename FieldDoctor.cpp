#include "FieldDoctor.hpp"

using namespace std;
using namespace pandemic;


Player& FieldDoctor::treat(City c){
    if (!board.is_connected(city, c)) {
        throw std::invalid_argument{"illegal action: not connected " + city_string(c)};
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