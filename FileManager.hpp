#include "includes.hpp"

using namespace std;

struct entry{
    int id;
    string data;
};

class FileManager{
private:
    static void separateStrings(string input, int& output1, string& output2){
        string return1 = "";
        string return2 = "";
        bool finished = false;
        bool first = true;
        if(input == ""){
            finished = true;
        }
        int i = 0;
        while(!finished){
            if(input[i] == ';'){
                finished = true;
            }else if(input[i] == ':'){
                first = false;
            }else if(input[i] == '\\'){
                i++;
                if(first){
                    return1 += input[i];
                }else{
                    return2 += input[i];
                }
            }
            i++;
        }
        output1 = stoi(return1);
        output2 = return2;
    }
    static void loadData(string path, vector<entry>& targetVector){
        ifstream file(path);
        string lineInFile;
        entry empty_entry;
        while(getline(file, lineInFile)){
            if(lineInFile == ""){break;}
            targetVector.push_back(empty_entry);
            separateStrings(lineInFile, targetVector.back().id, targetVector.back().data);
        }
        file.close();
    }
    static void saveData(string path, vector<entry>& targetVector){
        ofstream file(path);
        for(int i = 0; i < targetVector.size(); i++){
            for(int e = 0; e < to_string(targetVector[i].id).size(); e++){
                file << "\\" << to_string(targetVector[i].id)[e];
            }
            file << ":";
            for(int e = 0; e < targetVector[i].data.size(); e++){
                file << "\\" << targetVector[i].data[e];
            }
            file << ";" << endl;
        }
	    file.close();
    }
public:
    static const string MATERIAL_NAME_PATH;
    static const string MATERIAL_HARDNESS_PATH;
    static const string MATERIAL_COLOR_PATH;
    static void getEntries(string path, vector<entry>& targetVector){
        loadData(path, targetVector);
    }
    static void saveEntries(string path, vector<entry>& targetVector){
        saveData(path, targetVector);
    }
};
const string FileManager::MATERIAL_NAME_PATH = "./data/material_name.txt";
const string FileManager::MATERIAL_HARDNESS_PATH = "./data/material_hardness.txt";
const string FileManager::MATERIAL_COLOR_PATH = "./data/material_color.txt";