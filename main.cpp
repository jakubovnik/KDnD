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

        window.clear(sf::Color::Black);
        /*main_world.resetSelected();
        main_world.selectFirst();
        do{
            for(int y = 0; y < Chunk::CHUNK_SIZE; y++){
                for(int x = 0; x < Chunk::CHUNK_SIZE; x++){
                    Tile& tile = main_world.getSelected()->tiles[x][y];
                    if (tile.material.id != 0) {
                        sf::RectangleShape tileShape(sf::Vector2f(1,1)); // Example tile size
                        tileShape.setPosition(main_world.getSelected()->position.x * Chunk::CHUNK_SIZE+x,
                                               main_world.getSelected()->position.y * Chunk::CHUNK_SIZE+y);
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
        }while(main_world.selectNext());*/
        window.display();
    }
    return 0;
}