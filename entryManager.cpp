#include "DataManager.hpp"

void printEntries(vector<entry> target);
void printMaterials(DataManager& dm);

int main(){
    DataManager dm = DataManager();
    vector<entry> entries;
    bool editing_colors = false;
    while(true){
        string choice;
        cout << "Please input choice (c=colorMangement; e=exit): ";
        cin >> choice;
        if(choice == "exit" || choice == "e"){break;}
        else if(choice == "color" || choice == "c"){editing_colors = true;}
        

        while(editing_colors){
            printMaterials(dm);
            cout << endl << "Enter desired action \n(1=add[to back]; 2=remove; 3=edit; e=exit)\n: ";
            cin >> choice;
            if(choice == "e" || choice == "exit"){break;}
            else if(choice == "1"){
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
            }
        }
        editing_colors = false;
    }
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
