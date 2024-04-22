#include "WorldManager.hpp"

using namespace std;





int main(){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2i WINDOW_SIZE(desktopMode.width, desktopMode.height);
    
    World main_world;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "KDnD", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    int clicks = 0;

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
            main_world.getChunkAt(Chunk::convertToChunkPosition(mouse_position.x, mouse_position.y));
        }

        window.clear(sf::Color::Black);

        main_world.resetSelected();
        main_world.selectFirst();
        do{// TODO: deffinitley change this rendering loop, deffinitley dogshit
            for(int y = 0; y < Chunk::CHUNK_SIZE; y++){
                for(int x = 0; x < Chunk::CHUNK_SIZE; x++){
                    Tile& tile = main_world.getSelected()->tiles[x][y];
                    if (tile.material.id != 0) {
                        sf::RectangleShape tileShape(sf::Vector2f(1,1)); // Example tile size
                        tileShape.setPosition((main_world.getSelected()->position.x * Chunk::CHUNK_SIZE)+x,
                                               (main_world.getSelected()->position.y * Chunk::CHUNK_SIZE)+y);
                        if(tile.material.id == 1){
                            tileShape.setFillColor(sf::Color::Black); // Example color
                        }
                        if(tile.material.id == 2){
                            tileShape.setFillColor(sf::Color::Green); // Example color
                        }
                        if(tile.material.id == 3){
                            tileShape.setFillColor(sf::Color::Red); // Example color
                        }else{
                            tileShape.setFillColor(sf::Color::White);
                        }
                        window.draw(tileShape);
                    }
                }
            }
        }while(main_world.selectNext());
        window.display();
        // main_world.selectLast();
        // main_world.pushAfter(main_world.getSelected(), main_world.getSelected()->position.x+1, main_world.getSelected()->position.y+1);
        clicks = 0;
    }
    return 0;
}