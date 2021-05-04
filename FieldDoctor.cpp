#include "FieldDoctor.hpp"

using namespace pandemic;


Player& FieldDoctor::treat(City c){
    if (!board.is_connected(city, c)) {
        throw invalid_argument{"Execption: not connected " + cityToString(c)};
    }
    else if (board[c] == 0) {
        throw invalid_argument{"Execption: not enough cubes in city " + cityToString(c)};

    }
    else if (board.is_cure_discoverd(c)) {
        board[c] = 0;
    }
    else {
        board[c]--;
    }
    return *this;
}