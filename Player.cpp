#include "Player.hpp"

using namespace pandemic;



Player& Player::drive(City c){
    if(!board.is_connected(city, c)){ // if there is no connection throw exception
        throw invalid_argument{"Execption: " + cityToString(city) + " is not connected to " + cityToString(c)};
    }
    city = c;
    return *this;
}

Player& Player::fly_direct(City c){
    if(!cards.contains(c)){// if there is no card for this city throw execption
        throw invalid_argument{"Execption: card's " + cityToString(c)+"doesn't exist"};
    }
    cards.erase(c);
    city = c;
    return *this;
}

Player& Player::fly_charter(City c){
    if(cards.contains(city)){
        cards.erase(city);
        city = c;
        return *this;
    }
    throw invalid_argument{"Execption: card's " + cityToString(c)+"doesn't exist"};

}

Player& Player::fly_shuttle(City c){
    if(!board.is_research_station(city) || !board.is_research_station(c)){
        throw invalid_argument{"Execption: " + cityToString(city) + " and " + cityToString(c) + " must both have research station."};
    }
    city = c;
    return *this;
}

Player& Player::build(){
    if(!cards.contains(city)){
        throw invalid_argument{"Execption: research station faild, player must have a " + cityToString(city) + " card!"};
    }
    board.update_research_station(city);
    cards.erase(city);
    return *this;
}

Player& Player::discover_cure(Color c){
    if(!board.is_research_station(city)){
        throw invalid_argument{"Execption: city "+cityToString(city)+" must have research station!"};
    }
    int count = 0;
    for(const auto& t : cards){
        if(board.colorOf(t) == c){
            count++;
        }
    }
    if(count < CardLimit){
        throw invalid_argument{"Execption: there is only "+to_string(count)+" "+ colorToString(c) + " cards remaining " };
    }
    count = 1;
    for(auto it = cards.begin(); it != cards.end(); count++){
        if(count == CardLimit) { break; } 
        if(board.colorOf(*it) == c) {
            it = cards.erase(it);
        }
        else {
            ++it; 
        }
    }
    board.mark_cured(c);
    return *this;
}

Player& Player::treat(City c){
    if (city != c) {
        throw invalid_argument{"Execption: Outside of city" + cityToString(c)};
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

Player& Player::take_card(City c){
    cards.insert(c);
    return *this;
}