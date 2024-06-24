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
    int ratio;
public:
    longVector2i scroll;
    RenderData(vector2i target_window_size){
        scroll.x = 0;
        scroll.y = 0;
        window_size = target_window_size;
        ratio = 10;
    }
};