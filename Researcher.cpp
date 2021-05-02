#include "Researcher.hpp"

using namespace std;
using namespace pandemic;


Player& Researcher::discover_cure(Color c){
    int count = 0;
    for(const auto& t : cards){
        if(board.color_of(t) == c){
            count++;
        }
    }
    if(count < CardLimit){
        throw std::invalid_argument{"illegal action: you only have "+std::to_string(count)+" "+ color_string(c) + " cards remaining " };
    }
    count = 1;
    for(auto it = cards.begin(); it != cards.end(); count++){
        if(count == CardLimit) { break; }
        if(board.color_of(*it) == c) {
            it = cards.erase(it);
        }
        else {
            ++it;
        }
    }
    board.mark_cured(c);
    // std::cout << "The disease is cured: " << color_string(c) << std::endl;
    return *this;
}