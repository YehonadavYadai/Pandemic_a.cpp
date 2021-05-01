#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <iostream>
using namespace std;
namespace pandemic {

    class Board {

        static map<City, set<City>> connections; // the set of the citys that connected to each city
        map<City, int> diseas_cubes;
        set<City> research_stations;
        // set<Color> cure_discoverd;
        bool cured[4] = {0};

        public:
            Board() {}

            int& operator[](City c); // update diseas_cubes, for example board[City::HongKong]=2 means disease_cube[HongKong]=2
            bool is_clean(); // is the board clean from disease?
            bool is_connected(City& c1, City& c2); // is there connection between those two cities?
            void update_research_station(City c); // place reseach station in this city
            bool is_research_station(City c);// is there any reseach station in this city?
            void mark_cured(Color c); // mark cured's color that found.
            bool is_cure_discoverd(City c);  // is there any cure for color's disease that this city need?
            Color color_of(City c); // what the color's disease that this city got infected
            friend ostream& operator<<(ostream& out,const Board& b);
    };

//----------------------------------------------------------------------------------------------
    inline ostream& operator<<(ostream& out, const Board& b) {
        out << "-------------------------- BOARD --------------------------" << endl;
        out << "level of disease:" << endl;
        for(auto& i: b.diseas_cubes) { // HongKong:             2
            out << "\t" << city_string(i.first) << ": \t\t" << i.second << endl;
        }
        out << "Cure discovered for colors:" << endl;
        for(int i = 0; i < 4; i++) { // Yellow:             true
            out << "\t" << color_string(i) << ":\t\t" << b.cured[i] << endl;
        }
        out << "Research stations:" <<  endl;
        for(auto& i: b.research_stations) {// NewYork
            out << "\t" << city_string(i) << endl;
        }
        out <<  "------------------------ END BOARD ------------------------" << endl;
        return out;
    }
}
