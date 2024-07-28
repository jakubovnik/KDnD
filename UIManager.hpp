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
        setString("initialized");
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
    bool smooth_scroll;
    bool commit_scroll;
    longVector2i scroll;
    longVector2i target_scroll;
    vector<int> ratios;
public:
    RenderData(vector2i target_window_size){
        window_size = target_window_size;
        ratio = 1;
        target_ratio = 10;
        commit_scroll = true;
        smooth_scroll = false;
    }
    longVector2i& getScroll(){
        if(commit_scroll == false){
            return target_scroll;
        }
        return scroll;
    }
    longVector2i& addScroll(vector2i& difference){
        vector2i temp_vector = flipVector(difference);
        target_scroll = addVectorsI(scroll, temp_vector);
        return target_scroll;
    }
    void setScroll(longVector2i target){
        scroll = target;
        target_scroll = target;
    }
    void changeScroll(longVector2i target){
        target_scroll = target;
    }
    void openScroll(){
        commit_scroll = false;
    }
    void commitScroll(){
        commit_scroll = true;
        scroll = target_scroll;
    }
    void changeRatio(int number){//similar to setRatio, but only changes target_ratio, so that the ratio can be changed gradually instead of instantly (that update() uses)
        target_ratio = number;
    }
    void setRatio(float number){
        ratio = number;
    }
    float getRatio(){
        return ratio;
    }
    // float increaseRatio(){
    // }
    void update(){
        if(commit_scroll){
            if(smooth_scroll){
                //TODO: finish smooth scrolling
            }else{
                scroll = target_scroll;
            }
        }
        ratio =+ (target_ratio-ratio)/20;
    }
};

sf::Color getColorFromMaterial(material& target){
    return sf::Color(
        target.r,
        target.g,
        target.b
    );
}
sf::Vector2i toSfVectorI(vector2i& target){
    return sf::Vector2i(target.x, target.y);
}
sf::Vector2i toSfVectorI(longVector2i& target){
    return sf::Vector2i(target.x, target.y);
}
sf::Vector2f toSfVectorF(longVector2i target){
    return sf::Vector2f(target.x, target.y);
}
vector2i fromSfVectorI(sf::Vector2i target){
    return vector2i(target.x, target.y);
}
vector2i fromSfVectorI(sf::Vector2f target){
    return vector2i(target.x, target.y);
}
vector2i getMousePosition(){
    sf::Vector2i mouse_position = sf::Mouse::getPosition();
    return vector2i(mouse_position.x, mouse_position.y);
}
vector2i getRelativeMousePosition(RenderData& rd){
    vector2i absolute_mouse_position = getMousePosition();
    return vector2i(absolute_mouse_position.x+rd.getScroll().x, absolute_mouse_position.y+rd.getScroll().y);
}