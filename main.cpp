#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;



int main(){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2i WINDOW_SIZE(desktopMode.width, desktopMode.height);
    

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "KDnD", sf::Style::Fullscreen);
    while(window.isOpen()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
		}
    }
    return 0;
}