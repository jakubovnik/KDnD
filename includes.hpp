#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>

class vector2i{
public:
    int x;
    int y;
    vector2i(){
        x = 0;
        y = 0;
    }
    vector2i(int pos_x, int pos_y){
        x = pos_x;
        y = pos_y;
    }
};

class longVector2i{
public:
    long int x;
    long int y;
    longVector2i(){
        x = 0;
        y = 0;
    }
    longVector2i(long int pos_x, long int pos_y){
        x = pos_x;
        y = pos_y;
    }
};

// #include "includes.hpp"

int getRandomNumber(int min, int max) {
    // Initialize a random device to seed the random number engine
    std::random_device rd;
    std::mt19937 rng(rd());  // Mersenne Twister 19937 random number generator
    std::uniform_int_distribution<int> distribution(min, max);  // Uniform distribution of integers

    return distribution(rng);  // Generate and return a random integer
}

void debug(std::string messsage, int line){
    std::cout << messsage << std::endl << "On line: " << line << std::endl << std::endl;
    // debug("", __LINE__);
}