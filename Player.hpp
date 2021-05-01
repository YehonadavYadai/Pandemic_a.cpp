#pragma once
#include "Board.hpp"
#include "City.hpp"
#include <set>

namespace pandemic {

    class Player {

        protected:
            Board& board;
            std::set<City> cards;
            City city;
            std::string typeRole;

        public:
            inline Player(Board& b, City c, std::string r): board(b), city(c), typeRole(r){}

            Player& drive(City c);
            virtual Player& fly_direct(City c);
            Player& fly_charter(City c);
            Player& fly_shuttle(City c);
            virtual Player& build();
            virtual Player& discover_cure(Color c);
            virtual Player& treat(City c);
            inline string role(){return typeRole;}
            Player& take_card(City c);
    };
}