#include "DataManager.hpp"

void printEntries(vector<entry> target);
void printMaterials(DataManager& dm);

int main(){
    DataManager dm = DataManager();
    vector<entry> entries;
    bool editing_colors = false;
    while(true){
        string choice;
        cout << "\n\nPlease input choice\n(c=colorMangement; e=exit)\n: ";
        cin >> choice;
        if(choice == "exit" || choice == "e"){break;}
        else if(choice == "color" || choice == "c"){editing_colors = true;}


        while(editing_colors){
            printMaterials(dm);
            cout << endl << "Enter desired action \n(1=add[to back]; 2=remove; 3=edit; e=exit)\n: ";
            cin >> choice;
            if(choice == "e" || choice == "exit"){break;}
            printMaterials(dm);
            if(choice == "1"){
                string insert_name;
                string insert_hardness;
                string insert_r;
                string insert_g;
                string insert_b;
                cout << "Insert new name: ";
                cin >> insert_name;
                cout << "Insert new hardness: ";
                cin >> insert_hardness;
                cout << "Insert new color(r): ";
                cin >> insert_r;
                cout << "Insert new color(g): ";
                cin >> insert_g;
                cout << "Insert new color(b): ";
                cin >> insert_b;
                cout << "\nIs this correct?:\n" <<
                    insert_name << ", " <<
                    insert_hardness << ", " <<
                    "(" << insert_r << " , " << insert_g << " , " << insert_b << ")\n" <<
                    "y/n: ";
                cin >> choice;
                if(choice == "y" || choice == "Y" || choice == "yes"){
                    dm.addMaterial(insert_name, stoi(insert_hardness), stoi(insert_r), stoi(insert_g), stoi(insert_b));
                }
            }else if(choice == "2"){
                cout << "Insert the index of the unwanted material: ";
                cin >> choice;
                int temp_int = stoi(choice);
                cout << "\nDo you truly want to delete this?:\n" <<
                    dm.materials[temp_int].name << ", " <<
                    dm.materials[temp_int].hardness << ", " <<
                    "(" << dm.materials[temp_int].r << " , " <<
                    dm.materials[temp_int].g << " , " <<
                    dm.materials[temp_int].b << ")\n" <<
                    "y/n: ";
                cin >> choice;
                if(choice == "y" || choice == "Y" || choice == "yes"){
                    dm.materials.erase(dm.materials.begin()+temp_int);
                    cout << "Material erased" << endl << endl;
                }
            }else if(choice == "3"){
                string temp_string;
                string insert_name;
                string insert_hardness;
                string insert_r;
                string insert_g;
                string insert_b;
                int edited_index;
                cout << "Whitch material do you want to edit (index)?: ";
                cin >> edited_index;
                if(edited_index < dm.materials.size()){
                    cout << "Material found" << endl;
                }else{
                    cout << "Material not found, exiting edit" << endl;
                    break;
                }
                cout << "Insert edited name: ";
                // cin >> insert_name;
                cin >> temp_string;
                if(temp_string != "" || temp_string != " "){
                    insert_name = temp_string;
                }else{
                    insert_name = dm.materials[edited_index].name;
                }
                cout << "Insert edited hardness: ";
                // cin >> insert_hardness;
                cin >> temp_string;
                if(temp_string != "" || temp_string != " "){
                    insert_hardness = temp_string;
                }else{
                    insert_hardness = dm.materials[edited_index].hardness;
                }
                cout << "Insert edited color(r): ";
                // cin >> insert_r;
                cin >> temp_string;
                if(temp_string != "" || temp_string != " "){
                    insert_r = temp_string;
                }else{
                    insert_r = dm.materials[edited_index].r;
                }
                cout << "Insert edited color(g): ";
                // cin >> insert_g;
                cin >> temp_string;
                if(temp_string != "" || temp_string != " "){
                    insert_g = temp_string;
                }else{
                    insert_g = dm.materials[edited_index].g;
                }
                cout << "Insert edited color(b): ";
                // cin >> insert_b;
                cin >> temp_string;
                if(temp_string != "" || temp_string != " "){
                    insert_b = temp_string;
                }else{
                    insert_b = dm.materials[edited_index].b;
                }
                cout << "\nIs this correct?:\n" <<
                    insert_name << ", " <<
                    insert_hardness << ", " <<
                    "(" << insert_r << " , " << insert_g << " , " << insert_b << ")\n" <<
                    "y/n: ";
                cin >> choice;
                if(choice == "y" || choice == "Y" || choice == "yes"){
                    dm.materials[edited_index].name = insert_name;
                    dm.materials[edited_index].hardness = stoi(insert_hardness);
                    dm.materials[edited_index].r = stoi(insert_r);
                    dm.materials[edited_index].g  = stoi(insert_g);
                    dm.materials[edited_index].b = stoi(insert_b);
                }
            }
        }
        
        editing_colors = false;
    }
    dm.saveMaterials();
    return 0;
}

void printMaterials(DataManager& dm){
    for(int i = 0; i < dm.materials.size(); i++){
        cout << 
            i << ": " <<
            dm.materials[i].name << ", " <<
            dm.materials[i].hardness << ", " <<
            "(" << dm.materials[i].r << " , " << dm.materials[i].g << " , " << dm.materials[i].b << ")" <<
            endl;
    }
}

void printEntries(vector<entry> target){
    for(int i = 0; i < target.size(); i++){
        cout << target[i].id << ": " << target[i].data << endl;
    }
}
