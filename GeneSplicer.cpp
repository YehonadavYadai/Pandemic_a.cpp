#include "GeneSplicer.hpp"

using namespace std;
using namespace pandemic;

Player& GeneSplicer::discover_cure(Color c){
    if(!board.is_research_station(city)){
        throw std::invalid_argument{"illegal action: city "+city_string(city)+" has no research station!"};
    }
    if(cards.size() < 5){
        throw std::invalid_argument{"illegal action: you only have "+std::to_string(cards.size())+" "+ color_string(c) + " cards remaining " };
    }
    int count = 1;
    for(auto it = cards.begin(); it != cards.end(); count++){
        if(count == 5) { break; }
        it = cards.erase(it);
    }
    board.mark_cured(c);
    // std::cout << "The disease is cured: " << color_string(c) << std::endl;
    return *this;
}