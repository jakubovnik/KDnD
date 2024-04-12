#include "DataManager.hpp"

struct tile_material{
    unsigned int id : 8;
    unsigned int damage : 4;
};

struct chunk_position{
    long int x;
    long int y;
};


class Tile{
public:
    tile_material material;
    void damage(unsigned int damage){
        if(material.id == 0){
            return;
        }
        if(material.damage+damage > 15){
            setMaterial(0);
        }
    }
    void setMaterial(unsigned int id){
        material.damage = 0;
        material.id = id;
    }
};

class Chunk{
    Chunk* previous_ = nullptr;
    Chunk* next_ = nullptr;
public:
    static const int CHUNK_SIZE = 16;
    chunk_position position;
    int generated:2 = 0;
    Tile tiles[CHUNK_SIZE][CHUNK_SIZE];

    Chunk(long int x, long int y){
        position.x = x;
        position.y = y;
    }

    bool generateRandom(){
        if(generated){
            return false;
        }
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int x = 0; x < CHUNK_SIZE; x++){
                if(tiles[x][y].material.id != 0){
                    tiles[x][y].setMaterial(getRandomNumber(1,3));
                }
            }
        }
        generated = true;
        return true;
    }
};

class World{
private:
    Chunk origin_chunk = Chunk(0,0);
    Chunk* selected_ = &origin_chunk;
    int direction:3 = 0;//1=forward 2=forwardPass -1=back -2=backPass
public:
    Chunk& getChunkAt(long int pos_x, long int pos_y){//optimize later cause its propably dogshit
        if(pos_x == 0, pos_y == 0){
            return origin_chunk;
        }
        selected_ = &origin_chunk;
        if(selected_->position.y == pos_y){
            if(selected_->position.x > pos_x){
                direction = 1;
            }else{
                direction = -1;
            }
        }
        while(
            selected_->position.x != pos_x &&
            selected_->position.y != pos_y
        ){

        }
        return *selected_;
    }
};