#include "Color.hpp"
string color_string(int c) {

    if(c == 0) { return "yellow"; }
    if(c == 1) { return "red"; }
    if(c == 2) { return "blue"; }
    else { return "black"; }
}
