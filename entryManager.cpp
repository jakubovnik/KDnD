#include "DataManager.hpp"

using namespace std;

int main(){
    while(true){
        string choice;
        cout << "Please input path: ";
        cin >> choice;
        if(choice == "exit"){break;}
        fstream file(choice);
    }
    return 0;
}