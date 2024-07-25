#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

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



vector2i convertVector(longVector2i target){//use this carefully
    return vector2i(target.x, target.y);
}
longVector2i convertVector(vector2i target){//use this carefully
    return longVector2i(target.x, target.y);
}
vector2i addVectorsI(vector2i& vector1, vector2i& vector2){
    return vector2i(vector1.x+vector2.x,vector1.y+vector2.y);
}
longVector2i addVectorsI(longVector2i& vector1, vector2i& vector2){
    return longVector2i(vector1.x+vector2.x,vector1.y+vector2.y);
}
vector2i flipVector(vector2i& target){
    return vector2i(-target.x, -target.y);
}
longVector2i flipVector(longVector2i& target){
    return longVector2i(-target.x, -target.y);
}
// #include "includes.hpp"

int getRandomNumber(int min, int max) {// copied from chatGPT lol, is very slow propably and very bad :/
    // Initialize a random device to seed the random number engine
    std::random_device rd;
    std::mt19937 rng(rd());  // Mersenne Twister 19937 random number generator
    std::uniform_int_distribution<int> distribution(min, max);  // Uniform distribution of integers

    return distribution(rng);  // Generate and return a random integer
}

void debug(std::string message, int line){
    std::cout << message << std::endl << "On line: " << line << std::endl << std::endl;
    // debug("", __LINE__);
}

void die(std::string message, int line){
    std::cout << std::endl << std::endl;
    debug(message, line);
    exit(1);
}