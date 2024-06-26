#include "WorldManager.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Indicator{
    sf::Font* font;
    sf::Text text;
    sf::Texture texture;
public:
    Indicator(sf::Font& targetFont){
        setString("");
        font = &targetFont;
        text.setFont(*font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
    }
    void setString(string newString){
        text.setString(newString);
    }
    sf::Text getText(){
        return text;
    }
    void setPosition(int x, int y){
        text.setPosition(x, y);
    }
};

class RenderData{
    vector2i window_size;
    float ratio;
    float target_ratio;
public:
    longVector2i scroll;
    RenderData(vector2i target_window_size){
        scroll.x = 0;
        scroll.y = 0;
        window_size = target_window_size;
        ratio = 10;
        target_ratio = ratio;
    }
    void changeRatio(int number){//similar to setRatio, but only changes target_ratio, so that the ratio can be changed gradually instead of instantly (that update() uses)
        target_ratio = number;
    }
    void setRatio(float number){
        ratio = number;
    }
    // float increaseRatio(){
        
    // }
    void update(){
        ratio =+ (target_ratio-ratio)/20;
    }
};