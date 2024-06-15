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