#include "WorldManager.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class WorldPainter{// TODO: figure this shit out
    int radius;
    int outline_radius;
    World paint;
public:
    WorldPainter(){
        radius = 1;
        outline_radius = 1;
    }
    void paintOnWorld(World& target){
        // target.
    }
    void setRadius(int r){
        radius = r;
    }
};