#include "FileManager.hpp"

using namespace std;

struct material{
    unsigned int id : 8;
    string name;
    unsigned int hardness : 4;
};

class DataManager{
public:
    vector<material> materials;
    DataManager(){
        vector<entry> material_name = FileManager::getEntries(FileManager::MATERIAL_NAME_PATH);
        vector<entry> material_hardness = FileManager::getEntries(FileManager::MATERIAL_HARDNESS_PATH);
        for(int i = 0; i < material_name.size(); i++){
            material insert_material;
            insert_material.id = material_name[i].id,
            insert_material.name = material_name[i].data,
            insert_material.hardness = stoi(findEntryById(material_hardness, material_name[i].id).data);
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
};