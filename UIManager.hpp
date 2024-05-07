#include "WorldManager.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class WorldPainter{// TODO: figure this shit out
    int radius;
    int outline_radius;
    int material_id;
    int outline_material_id;
    World paint;
    World outline_paint;
public:
    WorldPainter(){
        radius = 1;
        outline_radius = 1;
    }
    int drawCircle(long int pos_x, long int pos_y){
        int pixels_drawn = 0;
        for(long int y = pos_y-radius; y < pos_y+radius; y++){
            for(long int x = pos_x-radius; x < pos_x+radius; x++){
                if(sqrt(abs(pos_x-x)*abs(pos_x-x) + abs(pos_y-y)*abs(pos_y-y))
                    <=
                    radius
                ){
                    paint.drawTile(x,y, 1);
                }
            }
        }
    }
    void paintOntoWorld(World& target){
        // target.
    }
    void setRadius(int r){
        radius = r;
    }
    void setMaterials(int target_id, int target_outline_id){
        material_id = target_id;
    }
};