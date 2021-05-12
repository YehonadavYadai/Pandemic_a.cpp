#pragma once
#include <map>
#define BLACK "\033[1m\033[30m"
#define RED "\033[1m\033[31m"
#define YELLOW "\033[1m\033[33m"
#define BLUE "\033[1m\033[34m"
#define RESET "\033[0m"
namespace pandemic
{
    enum Color
    {
        Red,
        Yellow,
        Blue,
        Black
    };
    inline std::string get_color(Color c)
    {
        switch (c)
        {
        case Red:
            return "Red";
            break;
        case Yellow:
            return "Yellow";
            break;
        case Blue:
            return "Blue";
            break;
        case Black:
            return "Black";
            break;
        }
    }
    inline std::string color_text(Color c)
    {
        switch (c)
        {
        case Red:
            return RED;
            break;
        case Yellow:
            return YELLOW;
            break;
        case Blue:
            return BLUE;
            break;
        case Black:
            return BLACK;
            break;
        }
    }

}