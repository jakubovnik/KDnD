#include "DataManager.hpp"

struct tile_material{
    unsigned int id : 8;
    unsigned int damage : 4;
};

class Tile{
public:
    tile_material material;
    Tile(){
        material.id = 0;
        material.damage = 0;
    }
    void damage(int damage){
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
    Chunk* previous_;
    Chunk* next_;
    static const int CHUNK_SIZE = 32;//preferably should be an exponent of 2
    vector2i position;
    bool generated;
    bool rendered;
    Tile tiles[CHUNK_SIZE][CHUNK_SIZE];

    Chunk(int x, int y):position(x, y){
        previous_ = nullptr;
        next_ = nullptr;
        generated = false;
        rendered = false;
    }
    /*~Chunk(){
        if(next_ != nullptr || (next_->position.x != 0 && next_->position.y != 0)){
            delete next_;
        }
        if(previous_ != nullptr || (previous_->position.x != 0 && previous_->position.y != 0)){
            delete previous_;
        }
    }*/

    void clear(int id){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int x = 0; x < CHUNK_SIZE; x++){
                tiles[x][y].setMaterial(id);
            }
        }
        generated = false;
        rendered = false;
    }
    void clear(){
        clear(0);
    }
    bool generateRandom(){//this function is EXTREMELY slow, like dogshit level slow (larger chunks => exponencially slow)
        if(generated){
            return false;
        }
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int x = 0; x < CHUNK_SIZE; x++){
                tiles[x][y].setMaterial(getRandomNumber(0,3));
            }
        }
        generated = true;
        rendered = false;
        return true;
    }
    static vector2i convertToChunkPosition(int pos_x, int pos_y){
        return vector2i(
            (pos_x-(pos_x%CHUNK_SIZE))/CHUNK_SIZE,
            (pos_y-(pos_y%CHUNK_SIZE))/CHUNK_SIZE
        );
    }
    static vector2i convertToChunkPosition(vector2i& pos){
        return convertToChunkPosition(pos.x, pos.y);
    }
};

class World{
private:
    Chunk origin_chunk;
    Chunk* selected_;
    int direction;//1=forward 2=forwardPass -1=back -2=backPass
public:
    bool cleared;
    World():origin_chunk(0,0){
        origin_chunk.clear();
        selected_ = &origin_chunk;
        direction = 0;
        origin_chunk.clear();
        cleared = false;
    }
    void resetSelected(){
        selected_ = &origin_chunk;
    }
    bool selectNext(){
        if(selected_->next_ == nullptr){
            return false;
        }
        selected_ = selected_->next_;
        return true;
    }
    bool selectPrevious(){
        if(selected_->previous_ == nullptr){
            return false;
        }
        selected_ = selected_->previous_;
        return true;
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
    void setSelected(Chunk* target_){
        selected_ = target_;
    }
    bool pushAfter(Chunk* target, int pos_x, int pos_y){//returns true if it the created chunk is last in line
        Chunk* temp_pointer_ = new Chunk(pos_x, pos_y);
        // temp_pointer_->generateRandom();
        if(target->next_ == nullptr){
            target->next_ = temp_pointer_;
            temp_pointer_->previous_ = target;
            return true;
        }else{
            temp_pointer_->next_ = target->next_;
            temp_pointer_->previous_ = target;
            target->next_->previous_ = temp_pointer_;
            target->next_ = temp_pointer_;
            return false;
        }
    }
    bool pushBefore(Chunk* target, int pos_x, int pos_y){//returns true if it the created chunk is first in line
        Chunk* temp_pointer_ = new Chunk(pos_x, pos_y);
        // temp_pointer_->generateRandom();
        if(target->previous_ == nullptr){
            target->previous_ = temp_pointer_;
            target->previous_->next_ = target;
            return true;
        }else{
            temp_pointer_->previous_ = target->previous_;
            temp_pointer_->next_ = target;
            target->previous_->next_ = temp_pointer_;
            target->previous_ = temp_pointer_;
            return false;
        }
    }
    void clear(){
        resetSelected();
        int n;
        for(n = 0; selectNext(); n++){}
        debug("To delete"+ to_string(n), __LINE__);
        for(int i = 0; i < n; i++){
            selectPrevious();
            delete selected_->next_;
            selected_->next_ = nullptr;
        }
        cleared = true;
    }
    Chunk* getChunkAt(int pos_x, int pos_y){
        if(selected_->position.x == pos_x && selected_->position.y == pos_y){
            return selected_;
        }
        direction = 0;
        if(selected_->position.y == pos_y){
            if(selected_->position.x < pos_x){
                direction = 1;
            }else if(selected_->position.x > pos_x){
                direction = -1;
            }else{
                die("dir sel 1", __LINE__);
            }
        }else if(selected_->position.y < pos_y){
            direction = 1;
        }else if(selected_->position.y > pos_y){
            direction = -1;
        }else{
            die("dir sel 2", __LINE__);//TODO: continue from here
        }
        while(!(selected_->position.x == pos_x && selected_->position.y == pos_y)){
            if(direction > 0){
                if(direction == 2){
                    pushBefore(selected_, pos_x, pos_y);
                    selectPrevious();
                    continue;
                }
                if(!selectNext()){
                    pushAfter(selected_, pos_x, pos_y);
                    selectNext();
                    continue;
                }
                if((selected_->position.y == pos_y && selected_->position.x > pos_x) || selected_->position.y > pos_y){
                    direction = 2;
                }
            }else{
                if(direction == -2){
                    pushAfter(selected_, pos_x, pos_y);
                    selectNext();
                    continue;
                }
                if(!selectPrevious()){
                    pushBefore(selected_, pos_x, pos_y);
                    selectPrevious();
                    continue;
                }
                if((selected_->position.y == pos_y && selected_->position.x < pos_x) || selected_->position.y < pos_y){
                    direction = -2;//AAAAAAAAAAAAAAAAAAAAAAAAa tak tady byl probléééém fuuuUUUUK MMEEEEEE AAAAA (byla kladná 2)
                }
            }
        }
        return selected_;
    }
    Chunk* getChunkAt(vector2i position_vector){
        return getChunkAt(position_vector.x, position_vector.y);
    }
    Tile* getTileAt(long int pos_x, long int pos_y){
        return &getChunkAt(Chunk::convertToChunkPosition(pos_x,pos_y))->tiles[pos_x%Chunk::CHUNK_SIZE][pos_y%Chunk::CHUNK_SIZE];
    }
    void drawTile(long int pos_x, long int pos_y, int id){
        getTileAt(pos_x, pos_y)->setMaterial(id);
        getChunkAt(Chunk::convertToChunkPosition(pos_x,pos_y))->rendered = false;
    }
    // long int ()
    int loadedChunks(){
        selectFirst();
        int loaded_chunks = 1;
        while(selectNext()){
            loaded_chunks++;
        }
        return loaded_chunks;
    }
//Painter part

};