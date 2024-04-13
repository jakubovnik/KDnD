#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// #include "includes.hpp"

int getRandomNumber(int min, int max) {// copied from chatgpt lol
    // Initialize random number generator with current time as seed
    std::mt19937 mt(static_cast<unsigned int>(time(0)));
    
    // Define distribution for integers between min and max (inclusive)
    std::uniform_int_distribution<int> dist(min, max);

    // Generate and return a random number
    return dist(mt);
}