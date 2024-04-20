#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// #include "includes.hpp"

int getRandomNumber(int min, int max) {
    // Initialize a random device to seed the random number engine
    std::random_device rd;
    std::mt19937 rng(rd());  // Mersenne Twister 19937 random number generator
    std::uniform_int_distribution<int> distribution(min, max);  // Uniform distribution of integers

    return distribution(rng);  // Generate and return a random integer
}

void debug(std::string messsage, int line){
    std::cout << messsage << std::endl << "On line: " << line << std::endl << std::endl << std::endl;
    // debug("", __LINE__);
}