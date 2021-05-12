#include "doctest.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;
using namespace std;

TEST_CASE("opearion"){
    Board board;
    City r = City::Algiers;
    OperationsExpert player{board, r};
    CHECK_NOTHROW(player.build());
    r= City::Atlanta;
    CHECK_NOTHROW(player.build());
    r= City::Karachi;
    CHECK_NOTHROW(player.build());
    r= City::Lagos;
    CHECK_NOTHROW(player.build());
    r= City::NewYork;
    CHECK_NOTHROW(player.build());
}


TEST_CASE("Test Virologist"){
    Board b;
    City c = City::Karachi;
    Virologist player{b, c};
    CHECK_THROWS(player.treat(c));
    player.take_card (c);
    CHECK_THROWS(player.treat(c));
    player.take_card(City::Santiago);
    b[City::Santiago]=6;
    CHECK_NOTHROW(player.treat(City::Santiago));
    c=City::Lagos;
    CHECK_THROWS(player.treat(c));

}

TEST_CASE(" Researcher"){
    Board b;
    City c=City::Johannesburg;
    Researcher player{b, c};
    CHECK_THROWS(player.discover_cure(Color::Yellow));
    player.take_card(c);
    player.take_card(City::Santiago);
    CHECK_THROWS(player.discover_cure(Color::Yellow));
    player.take_card(City::Johannesburg);
    CHECK_THROWS(player.discover_cure(Color::Yellow));
    player.take_card(City::Khartoum);
    CHECK_THROWS(player.discover_cure(Color::Yellow));
    player.take_card(City::Kinshasa);
    CHECK_NOTHROW(player.discover_cure(Color::Yellow));
}
TEST_CASE("methods"){
    Board board;
    OperationsExpert player(board, Atlanta);
    
    CHECK_NOTHROW(player.drive(Washington));//drive to a neighbor
    
    CHECK_THROWS(player.fly_charter(Cairo));
    CHECK_NOTHROW(player.take_card(Washington));
    CHECK_NOTHROW(player.fly_direct(Chicago));
    player.build();
    player.take_card(Cairo);
    player.take_card(Cairo);
    CHECK_NOTHROW(player.fly_charter(Chicago));
    CHECK_THROWS(player.build());
    player.take_card(Chicago);
    CHECK_NOTHROW(player.build());
    CHECK_NOTHROW(player.fly_charter(Cairo));
    player.take_card(Chicago);
    player.take_card(Essen);
    player.take_card(Atlanta);
    player.fly_direct(Chicago);
    player.take_card(Atlanta);
    player.take_card(London);
    player.take_card(Madrid);
    
    CHECK_THROWS(player.treat(Chicago));
    CHECK_THROWS(player.fly_shuttle(Atlanta));
    CHECK_THROWS(player.fly_shuttle(London));
    CHECK_THROWS(player.discover_cure(Red));
    CHECK_NOTHROW(player.discover_cure(Blue));
    CHECK_NOTHROW(player.treat(Chicago));
    player.take_card(London);
    CHECK_NOTHROW(player.fly_direct(Atlanta));
   

}