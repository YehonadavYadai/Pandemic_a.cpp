#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

#include "OperationsExpert.hpp"

using namespace pandemic;
using namespace std;

TEST_CASE("t1") {
    Board board;
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	board[City::Delhi] = 4;         // put 4 blue disease cube in Delhi
    OperationsExpert player {board, City::Algiers}; //black city
    player.take_card(Baghdad)
        .take_card(Delhi)
        .take_card(Istanbul)
        .take_card(Karachi)
        .take_card(Kolkata)
        .take_card(Moscow);
    CHECK_THROWS(player.discover_cure(Black)); //no research station in Algiers
    cout << board << endl;
    CHECK_THROWS(player.treat(Algiers)); //already 0
    CHECK_NOTHROW(player.fly_direct(Delhi));
    CHECK_NOTHROW(player.treat(Delhi)); //from 4 to 3
    cout << board[Delhi] << endl; // 3
    player.build(); //build a station in Algiers
    CHECK_NOTHROW(player.discover_cure(Black));
    cout << board << endl;
    cout << board[Delhi] << endl; // 0
    
    // CHECK_NOTHROW(player.fly_direct(Baghdad).fly_direct(Delhi).fly_direct(Istanbul).fly_direct(Karachi).fly_direct(Kolkata));
}