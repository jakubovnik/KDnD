#include "FileManager.hpp"

using namespace std;

struct material{
    string name;
    unsigned int hardness;
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

class DataManager{
public:
    vector<material> materials;
    DataManager(){
        vector<entry> material_name;
        FileManager::getEntries(FileManager::MATERIAL_NAME_PATH, material_name);
        vector<entry> material_hardness;
        FileManager::getEntries(FileManager::MATERIAL_HARDNESS_PATH, material_hardness);
        vector<entry> material_color;
        FileManager::getEntries(FileManager::MATERIAL_COLOR_PATH, material_color);
        for(int i = 0; i < material_name.size(); i++){
            material insert_material;
            insert_material.name = material_name[i].data;
            insert_material.hardness = stoi(findEntryById(material_hardness, material_name[i].id).data);
            splitColorData(findEntryById(material_color, material_name[i].id).data, insert_material.r, insert_material.g, insert_material.b);
            materials.push_back(insert_material);
        }
    }
    entry findEntryById(vector<entry> target_entry, unsigned int id){
        for(int i = 0; i < target_entry.size(); i++){
            if(target_entry[i].id == id){
                return target_entry[i];
            }
        }
        entry failed_entry;
        failed_entry.id = -1;
        failed_entry.data = "error";
        return failed_entry;
    }
    void splitColorData(string input, unsigned int& red, unsigned int& green, unsigned int& blue){
        int stage = 0;
        string color_red = "0";
        string color_green = "0";
        string color_blue = "0";
        for(int i = 0; i < input.size(); i++){
            if(input[i] == ','){
                stage++;
            }else{
                switch(stage){
                    case 0:
                        color_red += input[i];
                        debug(color_red, __LINE__);
                        break;
                    case 1:
                        color_green += input[i];
                        break;
                    case 2:
                        color_blue += input[i];
                        break;
                }
            }
        }
        red = stoi(color_red);
        green = stoi(color_green);
        blue = stoi(color_blue);
    }
    void addMaterial(string name, int hardness, int r, int g, int b){
        material insert_material;
        insert_material.name = name;
        insert_material.hardness = hardness;
        insert_material.r = r;
        insert_material.g = g;
        insert_material.b = b;
        materials.push_back(insert_material);
    }
    void saveMaterials(){
        entry insert_entry;
        vector<entry> material_name;
        vector<entry> material_hardness;
        vector<entry> material_color;
        for(int i = 0; i < materials.size(); i++){
            insert_entry.id = i;
            insert_entry.data = materials[i].name;
            material_name.push_back(insert_entry);

            insert_entry.data = to_string(materials[i].hardness);
            material_hardness.push_back(insert_entry);

            insert_entry.data = to_string(materials[i].r) +','+ to_string(materials[i].g) +','+ to_string(materials[i].b);
            material_color.push_back(insert_entry);
        }
        FileManager::saveEntries(FileManager::MATERIAL_NAME_PATH, material_name);
        FileManager::saveEntries(FileManager::MATERIAL_HARDNESS_PATH, material_hardness);
        FileManager::saveEntries(FileManager::MATERIAL_COLOR_PATH, material_color);
    }
};