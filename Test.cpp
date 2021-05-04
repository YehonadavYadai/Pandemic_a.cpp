/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 3.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-04
 ***********************************************************************************/

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

const int NUMBER_OF_TESTS = 30;

const vector<City> all_cities {
    City::Algiers,City::Atlanta,City::Baghdad,City::Bangkok,City::Beijing,City::Bogota,City::BuenosAires,City::Cairo,City::Chennai,
    City::Chicago,City::Delhi,City::Essen,City::HoChiMinhCity,City::HongKong,City::Istanbul,City::Jakarta,City::Johannesburg,
    City::Karachi,City::KePasio,City::Khartoum,City::Kinshasa,City::Kolkata,City::Lagos,City::Lima,City::London,City::LosAngeles,
    City::Madrid,City::Manila,City::MexicoCity,City::Miami,City::Milan,City::Montreal,City::Moscow,City::Mumbai,City::NewYork,
    City::Osaka,City::Paris,City::Riyadh,City::SanFrancisco,City::Santiago,City::SaoPaulo,City::Seoul,City::Shanghai,City::StPetersburg,
    City::Sydney,City::Taipei,City::Tehran,City::Tokyo,City::Washington
};
const map<City, Color> city_color {
    { City::Algiers, Color::Black },{ City::Atlanta, Color::Blue },{ City::Baghdad, Color::Black },{ City::Bangkok, Color::Red },
    { City::Beijing, Color::Red },{ City::Bogota, Color::Yellow },{ City::BuenosAires, Color::Yellow },{ City::Cairo, Color::Black },
    { City::Chennai, Color::Black },{ City::Chicago, Color::Blue },{ City::Delhi, Color::Black },{ City::Essen, Color::Blue },
    { City::HoChiMinhCity, Color::Red },{ City::HongKong, Color::Red },{ City::Istanbul, Color::Black },{ City::Jakarta, Color::Red },
    { City::Johannesburg, Color::Yellow },{ City::Karachi, Color::Black },{ City::Khartoum, Color::Yellow },{ City::Kinshasa, Color::Yellow },
    { City::Kolkata, Color::Black },{ City::Lagos, Color::Yellow },{ City::Lima, Color::Yellow },{ City::London, Color::Blue },
    { City::LosAngeles, Color::Yellow },{ City::Madrid, Color::Blue },{ City::Manila, Color::Red },{ City::MexicoCity, Color::Yellow },
    { City::Miami, Color::Yellow },{ City::Milan, Color::Blue },{ City::Montreal, Color::Blue },{ City::Moscow, Color::Black },
    { City::Mumbai, Color::Black },{ City::NewYork, Color::Blue },{ City::Osaka, Color::Red },{ City::Paris, Color::Blue },
    { City::Riyadh, Color::Black },{ City::SanFrancisco, Color::Blue },{ City::Santiago, Color::Yellow },{ City::SaoPaulo, Color::Yellow },
    { City::Seoul, Color::Red },{ City::Shanghai, Color::Red },{ City::StPetersburg, Color::Blue },{ City::Sydney, Color::Red },
    { City::Taipei, Color::Red },{ City::Tehran, Color::Black },{ City::Tokyo, Color::Red },{ City::Washington, Color::Blue }
};
const map<City, vector<City>> cities {
    { City::Algiers, {City::Madrid, City::Paris, City::Istanbul, City::Cairo } },
    { City::Atlanta, {City::Chicago, City::Miami, City::Washington } },
    { City::Baghdad, {City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi } },
    { City::Bangkok, {City::Kolkata, City::Chennai, City::Jakarta, City::HoChiMinhCity, City::HongKong } },
    { City::Beijing, {City::Shanghai, City::Seoul } },
    { City::Bogota, {City::MexicoCity, City::Lima, City::Miami, City::SaoPaulo, City::BuenosAires } },
    { City::BuenosAires, {Bogota, SaoPaulo } },
    { City::Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh } },
    { City::Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta } },
    { City::Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal } },
    { City::Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata } },
    { City::Essen, {London, Paris, Milan, StPetersburg } },
    { City::HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila } },
    { City::HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei } },
    { City::Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow } },
    { City::Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney } },
    { City::Johannesburg, {Kinshasa, Khartoum } },
    { City::Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi } },
    { City::Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg } },
    { City::Kinshasa, {Lagos, Khartoum, Johannesburg } },
    { City::Kolkata, {Delhi, Chennai, Bangkok, HongKong } },
    { City::Lagos, {SaoPaulo, Khartoum, Kinshasa } },
    { City::Lima, {MexicoCity, Bogota, Santiago } },
    { City::London, {NewYork, Madrid, Essen, Paris } },
    { City::LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney } },
    { City::Madrid, {London, NewYork, Paris, SaoPaulo, Algiers } },
    { City::Manila, {Taipei, SanFrancisco, HoChiMinhCity, Sydney } },
    { City::MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota } },
    { City::Miami, {Atlanta, MexicoCity, Washington, Bogota } },
    { City::Milan, {Essen, Paris, Istanbul } },
    { City::Montreal, {Chicago, Washington, NewYork } },
    { City::Moscow, {StPetersburg, Istanbul, Tehran } },
    { City::Mumbai, {Karachi, Delhi, Chennai } },
    { City::NewYork, {Montreal, Washington, London, Madrid } },
    { City::Osaka, {Taipei, Tokyo } },
    { City::Paris, {Algiers, Essen, Madrid, Milan, London } },
    { City::Riyadh, {Baghdad, Cairo, Karachi } },
    { City::SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila } },
    { City::Santiago, {Lima } },
    { City::SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid } },
    { City::Seoul, {Beijing, Shanghai, Tokyo } },
    { City::Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo } },
    { City::StPetersburg, {Essen, Istanbul, Moscow } },
    { City::Sydney, {Jakarta, Manila, LosAngeles } },
    { City::Taipei, {Shanghai, HongKong, Osaka, Manila } },
    { City::Tehran, {Baghdad, Moscow, Karachi, Delhi } },
    { City::Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco } },
    { City::Washington, {Atlanta, NewYork, Montreal, Miami } }
};


City random_connected_city(City c) {
    size_t adjes = (size_t)rand() % (size_t)cities.at(c).size();
    return cities.at(c).at(adjes);
}

City random_city() {
    size_t t = (size_t)rand() % 48;
    int i = 0;
    for(const auto& city: cities) {
        if(i == t) {
            return city.first;
        }
        i++;
    }
    return City::Algiers;
}

City random_city_colored(Color c) {
    while(true) {
        City r = random_city();
        if(city_color.at(r) == c) {
            return r;
        }
    }
    return City::Algiers;
}

set<City> pick_5_cities_colored(Color c) {
    set<City> ans;
    while(ans.size() < 5) {
        ans.insert(random_city_colored(c));
    }
    return ans;
}

set<City> pick_5_different_cities() {
    set<City> ans;
    while(ans.size() < 5) {
        ans.insert(random_city());
    }
    return ans;
}

TEST_CASE("Test OperationsExpert"){
    Board board;
    City r = City::Algiers;
    OperationsExpert player{board, r};
    CHECK_NOTHROW(player.build());
    r= City::Atlanta;
    CHECK_NOTHROW(player.build());
    r= City::Baghdad;
    CHECK_NOTHROW(player.build());
    r= City::Cairo;
    CHECK_NOTHROW(player.build());
    r= City::NewYork;
    CHECK_NOTHROW(player.build());
}
TEST_CASE("Test Dispatcher"){
    Board b;
    City c = City::Osaka;
    Dispatcher player{b, c};
    CHECK_NOTHROW(player.take_card(c));
    CHECK_NOTHROW(player.build());
    City c1 =City::Chicago;
    CHECK_NOTHROW(player.fly_direct(c1));
    CHECK_NOTHROW(player.take_card(c1));
    CHECK_NOTHROW(player.build());
    
}

/************************************************************************
 * חוקרת - Researcher:
 *                           ,יכולה לבצע פעולת "גילוי תרופה" בכל עיר 
 *                                         .לא חייבת להיות בתחנת מחקר
 */
TEST_CASE("Test Researcher"){
    srand(time(0));

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        Board b;
        Researcher player{b, random_city()};

        /* פעולה לא אפשרית - לחוקרת אין 5 קלפים מאותו צבע של העיר הנוכחית */
        for(Color color: {Color::Black, Color::Blue, Color::Red, Color::Yellow}) {
            CHECK_THROWS(player.discover_cure(color));
        }
        /*  fly_direct somewhere 
            -> take 5 different cities in the same color 
            -> discover cure for that color
            -> repeat 
        */
        for(int j = 0; j < 20; j++) {
            City dest = random_city();
            CHECK_NOTHROW(player.take_card(dest).fly_direct(dest));

            Color color = city_color.at(dest);

            for(City city: pick_5_cities_colored(color)) {
                CHECK_NOTHROW(player.take_card(city));
            }

            CHECK_NOTHROW(player.discover_cure(color));
        }
    }
}

/************************************************************************
 * פראמדיק - Medic:
 *                                    ,"כשהוא מבצע פעולת "טיפול במחלה
 *      .הוא מוריד את כל קוביות-המחלה מהעיר שהוא נמצא בה ולא רק אחת
 *                                    
 *                                         ,אם כבר התגלתה תרופה למחלה
 *      ,הוא אוטומטית מוריד את כל קוביות-המחלה מכל עיר שהוא נמצא בה
 *                                   ."גם בלי לבצע פעולת "טיפול במחלה
 */
// TEST_CASE("Test Medic"){
//     srand(time(0));

//     for(int i = 0; i < NUMBER_OF_TESTS; i++) {
//         Board b;
//         City start_city = random_city();
//         Medic player{b, start_city};
//         player.take_card(start_city);

//         /* פעולה לא אפשרית - לפראמדיק אין אף קלף */
//         for(City city: all_cities) {
//             CHECK_THROWS(player.treat(city));
//         }

//         /* מעבר רנדומלי בין הערים השונות */
//         for(int j = 0; j < 20; j++) {
//             City dest = random_city();
//             CHECK_NOTHROW(player.take_card(dest).fly_charter(dest));

//             b[dest] = 10;
//             CHECK(b[dest] == 10);
//             CHECK_NOTHROW(player.treat(dest));
//             CHECK(b[dest] == 0);
//         }
//     }
// }

/************************************************************************
 * וירולוגית - Virologist:
 *                                    ,"יכולה לבצע פעולת "טיפול במחלה
 *                       לא רק בעיר שהיא נמצאת בה, אלא בכל עיר בעולם
 *                                        .ע"י השלכת קלף של אותה העיר
 */
TEST_CASE("Test Virologist"){
    srand(time(0));
    Board b;

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        City start_city = random_city();
        Virologist player{b, start_city};

        for(City city: all_cities) {
            if(city != start_city) {
                /* פעולה לא אפשרית - לוירולוגית אין אף קלף */
                CHECK_THROWS(player.treat(city));
            }

            /* פעולה אפשרית - לוירולוגית יש את הקלף הדרוש */
            b[city] = 10;
            CHECK(b[city] == 10);
            CHECK_NOTHROW(player.take_card(city).treat(city));
            CHECK(b[city] == 9);
        }
    }
}

/************************************************************************
 * פורסת גנים - GeneSplicer:
 *               יכולה לבצע פעולת "גילוי תרופה" בעזרת 5 קלפים כלשהם
 *                                           .לא דווקא מהצבע של המחלה
 */
TEST_CASE("Test GeneSplicer"){
    srand(time(0));

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        Board b;
        City city = random_city();
        GeneSplicer player{b, city};
        CHECK_NOTHROW(player.take_card(city).build());

        /* פעולה לא אפשרית - לפורסת גנים אין 5 קלפים כלשהם */
        for(Color color: {Color::Black, Color::Blue, Color::Red, Color::Yellow}) {
            CHECK_THROWS(player.discover_cure(color));
        }

        Color color = city_color.at(city);

        /* בחירה של 5 ערים כלשהן בכל צבע אפשרי */
        for(City c: pick_5_different_cities()) {
            CHECK_THROWS(player.discover_cure(color));
            CHECK_NOTHROW(player.take_card(c));
        }

        CHECK_NOTHROW(player.discover_cure(color));
    }
}

/************************************************************************
 * רופא שטח - FieldDoctor:
 *           ,יכול לבצע פעולת "טיפול במחלה" לא רק בעיר שהוא נמצא בה 
 *            ,אלא בכל עיר סמוכה לעיר שהוא נמצא בה (ע"פ מפת הקשרים)
 *                                                .בלי להשליך קלף עיר
 */
TEST_CASE("Test FieldDoctor"){

}

// TEST_CASE("t1") {
//     board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
//     board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
//     board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
//     board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
//     board[City::Delhi] = 4;         // put 4 blue disease cube in Delhi
//     OperationsExpert player {board, City::Algiers}; //black city
//     player.take_card(Baghdad)
//         .take_card(Delhi)
//         .take_card(Istanbul)
//         .take_card(Karachi)
//         .take_card(Kolkata)
//         .take_card(Moscow);
//     CHECK_THROWS(player.discover_cure(Black)); //no research station in Algiers
//     CHECK_THROWS(player.treat(Algiers)); //already 0
//     CHECK_NOTHROW(player.fly_direct(Delhi));
//     CHECK_NOTHROW(player.treat(Delhi)); //from 4 to 3
//     cout << board[Delhi] << endl; // 3
//     player.build(); //build a station in Algiers
//     CHECK_NOTHROW(player.discover_cure(Black));
//     // cout << board << endl;
//     // cout << board[Delhi] << endl; // 0
    
//     // CHECK_NOTHROW(player.fly_direct(Baghdad).fly_direct(Delhi).fly_direct(Istanbul).fly_direct(Karachi).fly_direct(Kolkata));
// }