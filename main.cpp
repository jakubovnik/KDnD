#include "WorldManager.hpp"

using namespace std;



int main(){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2i WINDOW_SIZE(desktopMode.width, desktopMode.height);
    
    World main_world;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "KDnD", sf::Style::Fullscreen);
    while(window.isOpen()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
		}
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            main_world.getChunkAt(sf::Mouse::getPosition())->generateRandom();
        }

        window.clear(sf::Color::Transparent);
        main_world.selectFirst();
        do{
            for(int y = 0; y < Chunk::CHUNK_SIZE; y++){
                for(int x = 0; x < Chunk::CHUNK_SIZE; x++){
                    Tile& tile = main_world.getSelected()->tiles[x][y];
                    if (tile.material.id != 0) {
                        // Example rendering (replace with your own drawing logic)
                        sf::RectangleShape tileShape(sf::Vector2f(20.f, 20.f)); // Example tile size
                        tileShape.setPosition(main_world.getSelected()->position.x * Chunk::CHUNK_SIZE * 20.f + x * 20.f,
                                               main_world.getSelected()->position.y * Chunk::CHUNK_SIZE * 20.f + y * 20.f);
                        if(tile.material.id == 1){
                            tileShape.setFillColor(sf::Color::Black); // Example color
                        }
                        if(tile.material.id == 2){
                            tileShape.setFillColor(sf::Color::Green); // Example color
                        }
                        if(tile.material.id == 3){
                            tileShape.setFillColor(sf::Color::Red); // Example color
                        }
                        window.draw(tileShape);
                    }
                }
            }
        }while(main_world.selectNext());
        window.display();
    }
    return 0;
}