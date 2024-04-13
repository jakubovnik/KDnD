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
public:
    Chunk* previous_ = nullptr;
    Chunk* next_ = nullptr;
    static const int CHUNK_SIZE = 32;
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
    static chunk_position convertToChunkPosition(long int pos_x, long int pos_y){
        chunk_position returnPosition;
        returnPosition.x = (pos_x-(pos_x%CHUNK_SIZE))/CHUNK_SIZE;
        returnPosition.y = (pos_y-(pos_y%CHUNK_SIZE))/CHUNK_SIZE;
        return returnPosition;
    }
};

class World{
private:
    Chunk origin_chunk = Chunk(0,0);
    Chunk* selected_ = &origin_chunk;
    int direction:3 = 0;//1=forward 2=forwardPass -1=back -2=backPass
public:
    void resetSelected(){
        selected_ =&origin_chunk;
    }
    bool selectNext(){
        if(selected_->next_ == nullptr){
            return false;
        }
        selected_ = selected_->next_;
    }
    bool selectPrevious(){
        if(selected_->previous_ == nullptr){
            return false;
        }
        selected_ = selected_->previous_;
    }
    void selectFirst(){
        while(selected_->previous_!=nullptr){
            selectPrevious();
        }
    }
    void selectLast(){
        while(selected_->next_!=nullptr){
            selectNext();
        }
    }
    Chunk* getSelected(){
        return selected_;
    }
    bool pushAfter(Chunk& target, long int pos_x, long int pos_y){//returns true if it the created chunk is last in line
        Chunk* temp_pointer_ = new Chunk(pos_x, pos_y);
        if(target.next_ == nullptr){
            target.next_ = temp_pointer_;
            target.next_->previous_ = &target;
            return true;
        }else{
            temp_pointer_->next_ = target.next_;
            target.next_->previous_ = temp_pointer_;
            temp_pointer_->previous_ = &target;
            target.next_ = temp_pointer_;
            return false;
        }
    }
    bool pushBefore(Chunk& target, long int pos_x, long int pos_y){//returns true if it the created chunk is first in line
        Chunk* temp_pointer_ = new Chunk(pos_x, pos_y);
        if(target.previous_ == nullptr){
            target.previous_ = temp_pointer_;
            target.previous_->next_ = &target;
            return true;
        }else{
            temp_pointer_->previous_ = target.previous_;
            target.previous_->next_ = temp_pointer_;
            temp_pointer_->next_ = &target;
            target.previous_ = temp_pointer_;
            return false;
        }
    }
    Chunk* getChunkAt(sf::Vector2i position_vector){
        return getChunkAt(position_vector.x, position_vector.y);
    }
    Chunk* getChunkAt(long int pos_x, long int pos_y){//optimize later cause its propably dogshit
        if(pos_x == 0, pos_y == 0){
            return &origin_chunk;
        }
        selected_ = &origin_chunk;
        if(selected_->position.y == pos_y){
            if(selected_->position.x > pos_x){
                direction = 1;
            }else{
                direction = -1;
            }
        }else if(selected_->position.y > pos_y){
            direction = 1;
        }else{
            direction = -1;
        }
        while(
            selected_->position.x != pos_x &&
            selected_->position.y != pos_y
        ){
            if(direction > 0){
                if(direction == 2){
                    pushBefore(*selected_, pos_x, pos_y);
                    selectPrevious();
                    continue;
                }
                if(!selectNext()){
                    pushAfter(*selected_, pos_x, pos_y);
                    selectNext();
                    continue;
                }
                if((selected_->position.y == pos_y && selected_->position.x < pos_x) || selected_->position.y < pos_y){
                    direction = 2;
                }
            }else{
                if(direction == -2){
                    pushAfter(*selected_, pos_x, pos_y);
                    selectNext();
                    continue;
                }
                if(!selectPrevious()){
                    pushBefore(*selected_, pos_x, pos_y);
                    selectPrevious();
                    continue;
                }
                if((selected_->position.y == pos_y && selected_->position.x > pos_x) || selected_->position.y > pos_y){
                    direction = 2;
                }
            }
        }
        return selected_;
    }
};