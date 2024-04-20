#include "WorldManager.hpp"

using namespace std;





int main(){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2i WINDOW_SIZE(desktopMode.width, desktopMode.height);
    
    World main_world;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "KDnD", sf::Style::Fullscreen);

    int clicks = 0;

    while(window.isOpen()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
		}
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            clicks++;
        }

        window.clear(sf::Color::Black);

        debug("before reselect", __LINE__);
        main_world.resetSelected();
        debug("before selefirst", __LINE__);
        main_world.selectFirst();
        do{
            for(int y = 0; y < Chunk::CHUNK_SIZE; y++){
                for(int x = 0; x < Chunk::CHUNK_SIZE; x++){
                    debug("copying tile", __LINE__);
                    Tile& tile = main_world.getSelected()->tiles[x][y];
                    if (tile.material.id != 0) {
                        sf::RectangleShape tileShape(sf::Vector2f(1,1)); // Example tile size
                        debug("before setpos", __LINE__);
                        tileShape.setPosition((main_world.getSelected()->position.x * Chunk::CHUNK_SIZE)+x,
                                               (main_world.getSelected()->position.y * Chunk::CHUNK_SIZE)+y);
                        debug("before colors", __LINE__);
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
                        debug("before drawing", __LINE__);
                        window.draw(tileShape);
                    }
                }
            }
            debug("end of dowhile", __LINE__);
        }while(main_world.selectNext());
        window.display();
        clicks++;
        debug("clicks"+clicks, __LINE__);
    }
    return 0;
}