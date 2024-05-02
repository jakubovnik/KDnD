#include "WorldManager.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

sf::Color getColorFromMaterial(material& target);
sf::Vector2i toSfVectorI(vector2i& target);
vector2i getMousePosition();

int main(){
    DataManager dm = DataManager();
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    vector2i WINDOW_SIZE(desktopMode.width, desktopMode.height);
    // vector2i WINDOW_SIZE(800,600);
    
    World main_world;

    sf::RectangleShape drawing_pixel(sf::Vector2f(1,1));
    sf::RenderTexture screen_texture;
    screen_texture.create(WINDOW_SIZE.x, WINDOW_SIZE.y);
    screen_texture.clear(sf::Color::Transparent);
    screen_texture.display();
    sf::Sprite screen_sprite;
    screen_sprite.setTexture(screen_texture.getTexture());
    screen_sprite.setScale(1.0f, 1.0f);

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "KDnD", sf::Style::Fullscreen);
    window.setFramerateLimit(10);

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
            }
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
            vector2i mouse_position = getMousePosition();
            vector2i converted_mouse_position = Chunk::convertToChunkPosition(mouse_position);
            main_world.getChunkAt(converted_mouse_position)->clear(1);
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            vector2i mouse_position = getMousePosition();
            vector2i converted_mouse_position = Chunk::convertToChunkPosition(mouse_position);
            main_world.getChunkAt(converted_mouse_position)->generateRandom();
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            vector2i mouse_position = getMousePosition();
            vector2i converted_mouse_position = Chunk::convertToChunkPosition(mouse_position);
            main_world.getChunkAt(converted_mouse_position)->clear();
        }

        window.clear(sf::Color::Black);

        main_world.selectFirst();
        do{//TODO: not as dogshit as before, but still bad rendering (or really good, not really sure)
            if(
                main_world.getSelected()->position.x*Chunk::CHUNK_SIZE < 0 ||
                main_world.getSelected()->position.x*Chunk::CHUNK_SIZE > WINDOW_SIZE.x ||
                main_world.getSelected()->position.y*Chunk::CHUNK_SIZE < 0 ||
                main_world.getSelected()->position.y*Chunk::CHUNK_SIZE > WINDOW_SIZE.y
            ){
                main_world.getSelected()->rendered = false;
                continue;
            }
            if(main_world.getSelected()->rendered){
                continue;
            }
            for(int y = 0; y < Chunk::CHUNK_SIZE; y++){
                for(int x = 0; x < Chunk::CHUNK_SIZE; x++){
                    Tile& tile = main_world.getSelected()->tiles[x][y];
                    drawing_pixel.setPosition((main_world.getSelected()->position.x * Chunk::CHUNK_SIZE)+x,
                                            (main_world.getSelected()->position.y * Chunk::CHUNK_SIZE)+y);
                    if(tile.material.id < dm.materials.size()){
                        drawing_pixel.setFillColor(getColorFromMaterial(dm.materials[tile.material.id]));
                    }else{
                        drawing_pixel.setFillColor(sf::Color::White);
                    }
                    screen_texture.draw(drawing_pixel);
                }
            }
            main_world.getSelected()->rendered = true;
        }while(main_world.selectNext());
        screen_texture.display();
        window.draw(screen_sprite);
        
        window.display();
    }
    debug("Chunks: " + to_string(main_world.loadedChunks()), __LINE__);
    return 0;
}

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
vector2i getMousePosition(){
    sf::Vector2i mouse_position = sf::Mouse::getPosition();
    return vector2i(mouse_position.x, mouse_position.y);
}