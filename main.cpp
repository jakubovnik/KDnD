#include "WorldManager.hpp"

using namespace std;





int main(){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2i WINDOW_SIZE(desktopMode.width, desktopMode.height);
    
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
    window.setFramerateLimit(120);

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
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mouse_position = sf::Mouse::getPosition();
            sf::Vector2i converted_mouse_position = Chunk::convertToChunkPosition(mouse_position.x, mouse_position.y);
            main_world.getChunkAt(converted_mouse_position)->clear(1);
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
            sf::Vector2i mouse_position = sf::Mouse::getPosition();
            sf::Vector2i converted_mouse_position = Chunk::convertToChunkPosition(mouse_position.x, mouse_position.y);
            main_world.getChunkAt(converted_mouse_position)->generateRandom();
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            sf::Vector2i mouse_position = sf::Mouse::getPosition();
            sf::Vector2i converted_mouse_position = Chunk::convertToChunkPosition(mouse_position.x, mouse_position.y);
            main_world.getChunkAt(converted_mouse_position)->clear();
        }

        window.clear(sf::Color::Black);

        main_world.selectFirst();
        do{// TODO: deffinitley change this rendering loop, deffinitley dogshit
            if(main_world.getSelected()->rendered){
                continue;
            }
            for(int y = 0; y < Chunk::CHUNK_SIZE; y++){
                for(int x = 0; x < Chunk::CHUNK_SIZE; x++){
                    Tile& tile = main_world.getSelected()->tiles[x][y];
                    drawing_pixel.setPosition((main_world.getSelected()->position.x * Chunk::CHUNK_SIZE)+x,
                                            (main_world.getSelected()->position.y * Chunk::CHUNK_SIZE)+y);
                    switch (tile.material.id){
                    case 0:
                        drawing_pixel.setFillColor(sf::Color::Black);
                        break;
                    case 1:
                        drawing_pixel.setFillColor(sf::Color::Blue);
                        break;
                    case 2:
                        drawing_pixel.setFillColor(sf::Color::Green);
                        break;
                    case 3:
                        drawing_pixel.setFillColor(sf::Color::Red);
                        break;
                    default:
                        drawing_pixel.setFillColor(sf::Color::White);
                        break;
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
    return 0;
}