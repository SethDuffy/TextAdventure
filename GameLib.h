#ifndef GAME_LIB_H
#define GAME_LIB_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using std::string;
using std::endl;
using std::cout;
using std::cin;

struct Items{
	short int potion;
	int potAmount;
	short int atkCrystal;
	short int defCrystal;
	short int buffAmount;
};
struct Stats{
	std::string name;
	int maxHp;
	int currHp;
	int atk;
	int def;
	int crit;
	int gold;
	int area;
	int exp;
	int nextLevel;
	int level;
	Items item;
};

extern Stats player;
extern Stats enemy;

void save(){
	std::ofstream saveFile ("save.txt");
	saveFile << player.name << endl << player.maxHp << endl << player.currHp << endl
			 << player.atk << endl << player.def << endl << player.crit << endl 
			 << player.gold << endl << player.area << endl
			 << player.level << endl << player.exp << endl << player.nextLevel << endl
			 << player.item.potion << endl << player.item.atkCrystal << endl 
			 << player.item.defCrystal << endl << player.item.potAmount << endl
			 << player.item.buffAmount << endl;
	saveFile.close();

	cout << "GameState succefully saved\n";

	return;
}
void loadSave(){
	std::ifstream save("save.txt");
	if(save){
   		int i = 0;
   		string value;

   		while(save >> value){
   			if(i == 0)
   				player.name = value;
   			if(i == 1)
   				player.maxHp = stoi(value);
   			if(i == 2)
   				player.currHp = stoi(value);
   			if(i == 3)
   				player.atk = stoi(value);
   			if(i == 4)
   				player.def = stoi(value);
   			if(i == 5)
   				player.crit = stoi(value);
   			if(i == 6)
   				player.gold = stoi(value);
   			if(i == 7)
   				player.area = stoi(value);
   			if(i == 8)
   				player.level = stoi(value);
   			if(i == 9)
   				player.exp = stoi(value);
   			if(i == 10)
   				player.nextLevel = stoi(value);
   			if(i == 11)
				player.item.potion = stoi(value);
   			if(i == 12)
   				player.item.atkCrystal = stoi(value);
   			if(i == 13)
   				player.item.defCrystal = stoi(value);
   			if(i == 14)
   				player.item.potAmount = stoi(value);
   			if(i == 15)
   				player.item.buffAmount = stoi(value);
   			++i;
   		}
   		cout << "File loaded succefully\n";
   	}
   	save.close();

}
int clamp(int x, int y, int var){
	if(var < x)
		return var = x;
	else if(var > y)
		return var = y;
	else
		return var;
}
char getInput(){
	char input;
	cin >> input;
	cout << endl;
	return input;
}
void displayStats(){
	cout << "Name             " << player.name << endl
		 << "Health           " << player.currHp << endl
		 << "Defense          " << player.def << endl
		 << "Attack           " << player.atk << endl
		 << "Crit Chance      20" << (char)37 << endl
		 << "Crit Damage      " << player.crit << endl
		 << "Gold             " << player.gold << endl
		 << "Experience       " << player.exp << endl
		 << "Level            " << player.level << endl
		 << "Next Level Exp   " << player.nextLevel << endl
		 << "Potions          " << player.item.potion << endl
		 << "Attack Crystals  " << player.item.atkCrystal << endl
		 << "Defense Crystals " << player.item.defCrystal << endl
		 << "(1)To leave" << endl;
	short temp;
	cin >> temp;
	cout << endl;
	return;
}
void playerStatus(){
	if(player.name.empty()){
		cout << "what is your name adventurer?\n";
		cin >> player.name;
		cout << endl;
	}
	cout << "Your hp is " << player.currHp << endl;
	return;
}
void enemyStatus(){
	cout << enemy.name << "'s hp is " <<  enemy.currHp << endl;
	return;
}
#endif