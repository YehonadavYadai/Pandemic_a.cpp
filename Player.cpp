#include "Player.hpp"

using namespace std;
using namespace pandemic;


//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::drive(City c){
    if(!board.is_connected(city, c)){ // if there is no connection throw exception
        throw std::invalid_argument{"Illegal action: " + city_string(city) + " is not connected to " + city_string(c)};
    }
    city = c;
    // std::cout << "drive() current city: " << city_string(city) << std::endl;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::fly_direct(City c){
    if(cards.find(c)==cards.end()){// if there is no card for this city throw execption
        throw std::invalid_argument{"Illegal action: you do not have the card of " + city_string(c)};
    }
    cards.erase(c);
    city = c;
    // std::cout << "fly_direct() current city: " << city_string(city) << std::endl;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::fly_charter(City c){
    return fly_direct(c);
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::fly_shuttle(City c){
    if(!board.is_research_station(city) || !board.is_research_station(c)){
        throw std::invalid_argument{"Illegal action: " + city_string(city) + " and " + city_string(c) + " must both have research station."};
    }
    city = c;
    // std::cout << "fly_shuttle() current city: " << city_string(city) << std::endl;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::build(){
    if(cards.find(city)==cards.end()){
        throw std::invalid_argument{"Cant build research station! the player dont have a " + city_string(city) + " card"};
    }
    board.update_research_station(city);
    cards.erase(city);
    // std::cout << "build() build in city: " << city_string(city) << std::endl;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::discover_cure(Color c){
    if(!board.is_research_station(city)){
        throw std::invalid_argument{"illegal action: city "+city_string(city)+" has no research station!"};
    }
    int count = 0;
    for(auto& t : cards){
        if(board.color_of(t) == c)
            count++;
    }
    if(count < 5){
        throw std::invalid_argument{"illegal action: you only have "+to_string(count)+" "+ color_string(c) + " cards remaining " };
    }
    count = 0;
    // for(auto it = cards.begin(); it < cards.end(); count++){
    for(auto it = cards.begin(); it != cards.end(); count++){
        if(count == 4) { break; } // can remove if we set first for < insted of != or should be count== 5
        if(board.color_of(*it) == c) {
            it = cards.erase(it);
        }
        else {
            ++it; // it++
        }
    }
    board.mark_cured(c);
    // std::cout << "The disease is cured: " << color_string(c) << std::endl;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::treat(City c){
    if (city != c) {
        throw std::invalid_argument{"illegal action: you are not in city " + city_string(c)};
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

//------------------------------------------------------------------------------------------------------------------------------------------
Player& Player::take_card(City c){
    cards.insert(c);
    return *this;
}