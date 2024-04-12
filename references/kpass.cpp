#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <type_traits>
#include <Windows.h>

using namespace std;

class passwordStrings{
public:
	string name;
	string password;
	passwordStrings(string name, string password){
		this->name = name;
		this->password = password;
	}
	void setStrings(string name, string password){
		this->name = name;
		this->password = password;
	}
};

void separatePassword(string input, string& output1, string& output2);
void loadPasswords(string path, vector<passwordStrings>& targetVector);
void addPassword(string name, string password, vector<passwordStrings> &target, string seed);
void savePasswords(string path, vector<passwordStrings>& passwords);
void updateOutput(vector<passwordStrings>& input, vector<passwordStrings> &output, string seed);

int main(){
	bool show_text_areas = true;
	bool show_items = true;
	
	const sf::Vector2i WINDOW_SIZE(400, 1080);
	const sf::Vector2f TEXT_AREA_SIZE(350,40);
	const sf::Vector2f ITEM_AREA_SIZE(380, 35);
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "myPass",sf::Style::None);
	window.setPosition(sf::Vector2i(0,0));
	HWND hwnd = window.getSystemHandle(); // Get handle to your application window
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
	sf::Font arial;
	arial.loadFromFile("data/Arialn.ttf");
	sf::Text text;
	text.setFont(arial);
	sf::Text codeText;
	string codeString;
	sf::Text nameText;
	string nameString;
	sf::Text passwordText;
	string passwordString;
	codeText.setFont(arial);
	nameText.setFont(arial);
	passwordText.setFont(arial);
	codeText.setStyle(sf::Text::Style::Bold);
	string* stringPtrs[] = {&codeString, &nameString, &passwordString};
	sf::Text* textPtrs[] = {&codeText, &nameText, &passwordText};
	int focused_text = 0;
	
	
	sf::RectangleShape cyanBox(TEXT_AREA_SIZE);
	cyanBox.setFillColor(sf::Color::Transparent);
	cyanBox.setOutlineThickness(3);
	cyanBox.setOutlineColor(sf::Color::Cyan);
	sf::RectangleShape redBox(TEXT_AREA_SIZE);
	redBox.setFillColor(sf::Color::Transparent);
	redBox.setOutlineThickness(3);
	redBox.setOutlineColor(sf::Color::Red);
	sf::RectangleShape blueRect(ITEM_AREA_SIZE);
	blueRect.setFillColor(sf::Color::Blue);
	sf::RectangleShape underline_blueRect(sf::Vector2f(ITEM_AREA_SIZE.x, 2));
	underline_blueRect.setFillColor(sf::Color::Cyan);
	
	vector<passwordStrings> passwordVector;
	vector<passwordStrings> outputVector;
	loadPasswords("passwords.txt", passwordVector);
	
	
	while (window.isOpen()){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
			if(passwordVector.size() != 0){
				for(int i = 0; i < outputVector.size(); i++){
					cout << outputVector[i].name << ": " << outputVector[i].password << endl;
				}
			}
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)||sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))){
			if(nameText.getString() != "" &&
			passwordText.getString()!= "" &&
			codeText.getString().getSize() >= nameText.getString().getSize()+passwordText.getString().getSize()){
				addPassword(nameText.getString(), passwordText.getString(), passwordVector, codeText.getString());
				nameText.setString("");
				nameString.clear();
				passwordText.setString("");
				passwordString.clear();
			}
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)||sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))){
			stringPtrs[focused_text]->clear();
			textPtrs[focused_text]->setString("");
		}sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}else if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 127 && event.text.unicode > 31) { // all usable chars
					stringPtrs[focused_text]->push_back(static_cast<char>(event.text.unicode));
				}else if (event.text.unicode == 8 && stringPtrs[focused_text]->size() > 0) {
					stringPtrs[focused_text]->pop_back(); // Backspace
				}else if(event.text.unicode == 9){ // Tab
					focused_text++;
					if(focused_text > 2){// EDIT THIS if more text areas are added
						focused_text = 0;
					}
				}
				textPtrs[focused_text]->setString(*stringPtrs[focused_text]);
			}
		}
		
		window.clear(sf::Color::Transparent);
		if(show_text_areas){
			for(int i = 0; i<3; i++){
				textPtrs[i]->setPosition(25, i*50+10);
				textPtrs[i]->setFillColor(sf::Color::Cyan);
				if(i == focused_text){
					textPtrs[i]->setFillColor(sf::Color::White);
					redBox.setPosition(25, i*50+10);
					window.draw(*textPtrs[i]);
					window.draw(redBox);
				}else{
					cyanBox.setPosition(25, i*50+10);
					window.draw(*textPtrs[i]);
					window.draw(cyanBox);
				}
			}
		}
		if(show_items){
			updateOutput(passwordVector, outputVector, codeText.getString());
			for(int i = 0; i < outputVector.size(); i++){
				blueRect.setPosition(10, i*50+200);
				window.draw(blueRect);
				underline_blueRect.setPosition(10, i*50+201+ITEM_AREA_SIZE.y);
				window.draw(underline_blueRect);
				text.setString(outputVector[i].name);
				text.setPosition(15, i*50+200);
				window.draw(text);
				text.setString(outputVector[i].password);
				text.setPosition(WINDOW_SIZE.x-text.getGlobalBounds().width-15, i*50+200);
				window.draw(text);
			}
		}
		window.display();
	}
	savePasswords("passwords.txt", passwordVector);
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void separatePassword(string input, string& output1, string& output2){
	output1 = "";
	output2 = "";
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
				output1 += input[i];
			}else{
				output2 += input[i];
			}
		}
		i++;
	}
}

void loadPasswords(string path, vector<passwordStrings>& targetVector){
	fstream passwordFile(path);
	string lineInFile;
	while(getline(passwordFile, lineInFile)){
		targetVector.push_back(passwordStrings("",""));
		separatePassword(lineInFile, targetVector[targetVector.size()-1].name, targetVector[targetVector.size()-1].password);
	}
	passwordFile.close();
}

void addPassword(string name, string password, vector<passwordStrings>& target, string seed){
	target.push_back(passwordStrings("",""));
	char weird_char;
	int index = 0;
	for(int i = 0; i < name.size(); i++){
		weird_char = ~(name[i]+seed[index]);
		target[target.size()-1].name+=weird_char;
		index++;
	}
	for(int i = 0; i < password.size(); i++){
		weird_char = ~(password[i]+seed[index]);
		target[target.size()-1].password+=weird_char;
		index++;
	}
}

void savePasswords(string path, vector<passwordStrings>& passwords){
	ofstream clearDis(path);
	clearDis.close();
	fstream passwordFile(path);
	for(int i = 0; i < passwords.size(); i++){
		for(int e = 0; e < passwords[i].name.size(); e++){
			passwordFile << "\\" << passwords[i].name[e];
		}
		passwordFile << ":";
		for(int e = 0; e < passwords[i].password.size(); e++){
			passwordFile << "\\" << passwords[i].password[e];
		}
		passwordFile << ";" << endl;
	}
	passwordFile.close();
}

void updateOutput(vector<passwordStrings>& input, vector<passwordStrings>& output, string seed){
	output.clear();
	int index;
	char normal_char;
	for(int e = 0; e < input.size(); e++){
		output.push_back(passwordStrings("",""));
		index = 0;
		for(int i = 0; i < input[e].name.size(); i++){
			normal_char = (~input[e].name[i])-seed[index];
			output[e].name+=normal_char;
			index++;
		}
		for(int i = 0; i < input[e].password.size(); i++){
			normal_char = (~input[e].password[i])-seed[index];
			output[e].password+=normal_char;
			index++;
		}
	}
}