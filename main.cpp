#include "UIManager.hpp"

using namespace std;

int main(){
    //getting window data
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    vector2i WINDOW_SIZE(desktopMode.width, desktopMode.height);
    //setting manager objects
    RenderData rd = RenderData(WINDOW_SIZE);
    DataManager dm = DataManager();
    WorldData main_world;
    // vector2i WINDOW_SIZE(800,600);

    //setting text stuff
    sf::Font default_font;
    default_font.loadFromFile("data/fonts/ARIAL.TTF");
    vector<Indicator> indicators;
    indicators.push_back(Indicator(default_font));
    indicators.push_back(Indicator(default_font));
    indicators.push_back(Indicator(default_font));
    indicators.push_back(Indicator(default_font));
    indicators.push_back(Indicator(default_font));

    sf::RectangleShape drawing_pixel(sf::Vector2f(1,1));
    sf::RenderTexture screen_texture;
    screen_texture.setSmooth(true);
    screen_texture.create(WINDOW_SIZE.x, WINDOW_SIZE.y);
    screen_texture.clear(sf::Color::Transparent);
    screen_texture.display();
    sf::Sprite screen_sprite;
    screen_sprite.setTexture(screen_texture.getTexture());
    screen_sprite.setScale(1.0f, 1.0f);

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "KDnD", sf::Style::Fullscreen);
    window.setFramerateLimit(120);

    //testing variables (TODO: remove or improve later)
    vector2i temp_vector;
    longVector2i temp_long_vector;
    vector2i starting_mouse_pos;
    vector2i mouse_difference;
    bool middle_held_down = false;
    vector2i mouse_pos;
    int rendered_chunks = 0;

    while(window.isOpen()){/////////////////////////////////////////////////////////////////////////////////////////main loop
        sf::Event event;
        mouse_pos = getMousePosition();
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
                if(event.key.code == sf::Keyboard::R){//TODO: make this less easy to do
                    main_world.clear();
                }
            }
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Button::Middle){
                    rd.openScroll();
                    starting_mouse_pos = mouse_pos;
                    middle_held_down = true;
                }
            }
            if(event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Button::Middle){
                    rd.commitScroll();
                    mouse_difference = mouse_pos;
                    middle_held_down = false;
                }
            }
        }
        if(middle_held_down){
            temp_vector = flipVector(starting_mouse_pos);
            mouse_difference = addVectorsI(mouse_pos, temp_vector);
            rd.addScroll(mouse_difference);
            main_world.selectFirst();
            do{
                main_world.getSelected()->rendered = false;
            }while(main_world.selectNext());
            screen_texture.clear();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            main_world.drawCircle(10, 0, 30);
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            vector2i mouse_position = getRelativeMousePosition(rd);
            main_world.drawCircle(mouse_position.x, mouse_position.y, 40);
        }

        rd.update();

        window.clear(sf::Color::Black);


        if(main_world.cleared){
            screen_texture.clear();
            main_world.cleared = false;
            main_world.getSelected()->rendered == false;
        }

        rendered_chunks = 0;
        main_world.selectFirst();
        do{//TODO: Fix rendering, not as dogshit as before, but still bad rendering (or really good, not really sure) also make it work with threads
            if(
                main_world.getSelected()->position.x*Chunk::CHUNK_SIZE < 0 + rd.getScroll().x ||
                main_world.getSelected()->position.x*Chunk::CHUNK_SIZE > WINDOW_SIZE.x + rd.getScroll().x ||
                main_world.getSelected()->position.y*Chunk::CHUNK_SIZE < 0 + rd.getScroll().y ||
                main_world.getSelected()->position.y*Chunk::CHUNK_SIZE > WINDOW_SIZE.y + rd.getScroll().y
            ){
                main_world.getSelected()->rendered = false;
                continue;
            }
            rendered_chunks++;
            if(main_world.getSelected()->rendered){
                continue;
            }
            for(int y = 0; y < Chunk::CHUNK_SIZE; y++){
                for(int x = 0; x < Chunk::CHUNK_SIZE; x++){
                    Tile& tile = main_world.getSelected()->tiles[x][y];
                    drawing_pixel.setPosition((main_world.getSelected()->position.x * Chunk::CHUNK_SIZE)+x - rd.getScroll().x,
                                            (main_world.getSelected()->position.y * Chunk::CHUNK_SIZE)+y - rd.getScroll().y);
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
        // screen_sprite.setPosition(toSfVectorF(flipVector(rd.getScroll())));
        window.draw(screen_sprite);

        // Indicator updating
        indicators.at(0).setString(to_string(main_world.loadedChunks()));
        indicators.at(1).setString(
            "x: " + to_string(mouse_pos.x-starting_mouse_pos.x) + " " +
            "y: " + to_string(mouse_pos.y-starting_mouse_pos.y)
        );
        indicators.at(2).setString(
            "x: " + to_string(rd.getScroll().x) + " " +
            "y: " + to_string(rd.getScroll().y)
        );
        indicators.at(3).setString(to_string(rd.getRatio()));
        indicators.at(4).setString(to_string(rendered_chunks));
        // Indicator drawing
        for(int i = 0; i < indicators.size(); i++){
            indicators.at(i).setPosition(0, i*30);
            window.draw(indicators.at(i).getText());
        }
        
        window.display();
    }
    debug("Chunks: " + to_string(main_world.loadedChunks()), __LINE__);
    return 0;
}

