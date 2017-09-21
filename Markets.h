#ifndef _MARKET_
#define _MARKET_

#include "GameLib.h"

void market1();
void generalStore();
void bladeShop();
void creepyLady();

void marketDef(){
	if(player.area == 1)
		market1();
	else 
		return;
}

void market1(){ //Branching tree for the first areas shops
	cout << "You see many shops lining the streets\nWhich one will you enter?\n(1)Devon's General Store\n"
		 << "(2)Aidan's Blade Shop\n(3)Jack's Creepy Shop\n(4)Leave\n"
		 << "You have " << player.gold << " gold\n";

	int input;
	cin >> input;
	cout << endl;

	switch (input){
		case 1 :
			generalStore();
			break;
		case 2 :
			bladeShop();
			break;
		case 3 : 
			creepyLady();
			break;
	}

	return;
}
//Place for the player to buy potions and attack crystals
void generalStore(){
	cout << "A simple yet useful selection is presented to you\n(1)Potion(5g)\n"
		 <<													   "(2)Attack Crystal(4g)\n"
		 <<													   "(3)Defence Crystal(3g)\n"
		 <<													   "(4)Leave\n";

	int input;	 
	cin >> input;
	cout << endl;

	switch(input){
		case 1 :
			if(player.gold >= 5 && player.item.potion < 2){
				player.item.potion += 1;
				player.gold -= 5;
				cout << "You now have " << player.item.potion << " potions\nAnd " << player.gold << " gold\n";
			}
			else if(player.gold < 4) cout << "Insufficient funds\n(" << player.gold << "g)\n";
			else cout << "Max potion count of (" << player.item.potion << ") reached\n";
			break;
		case 2 :
			if(player.gold > 3 && (player.item.atkCrystal + player.item.defCrystal) < 3){
				player.item.atkCrystal += 1;
				player.gold -= 4;
				cout << "You now have " << player.item.atkCrystal << " attack crystals\nAnd " << player.gold << " gold\n";
			}
			else if(player.gold < 4) cout << "Insufficient funds\n(" << player.gold << "g)\n";
			else cout << "Max crystal count of (" << player.item.atkCrystal + player.item.defCrystal << ") reached\n";
			break;
		case 3 :
			if(player.gold > 2 && (player.item.atkCrystal + player.item.defCrystal) < 3){
				player.item.defCrystal += 1;
				player.gold -= 3;
				cout << "You now have " << player.item.defCrystal << " defence crystals\nAnd " << player.gold << " gold\n";
			}
			else if(player.gold < 4) cout << "Insufficient funds\n(" << player.gold << "g)\n";
			else cout << "Max crystal count reached\n";
			break;
	}
	return;
}
//Shop For the player to increase their attack
void bladeShop(){
	int input;

	if(player.gold < 30){
		cout << "The shop has standard wares for its kind; but you don't have the funds to buy anything\n";
		return;
	}
	else {
		cout << "You admire the exquisite blades draping the walls\nWhat will you purchase\n"
			 << "(1)Dinky Blade(30g)(+1atk)\n(2)Copper Blade(50g)(+2atk)\n"
			 << "(3)Iron Blade(80g)(+4atk)\n(4)Master Blade(150g)(+7atk)\n";

		cin >> input;
		cout << endl;
		
		switch (input){
			case 1 :
				if(player.gold >= 30){
					player.atk = 2;
					player.atk += 1;
					player.gold -= 30;
				}
				break;
			case 2 :
				if(player.gold >= 50){
					player.atk = 2;
					player.atk += 2;
					player.gold -= 50;
				}
				break;
			case 3 :
				if(player.gold >= 80){
					player.atk = 2;
					player.atk += 4;
					player.gold -= 80;
				}
				break;
			case 4 :
				if(player.gold >= 150){
					player.atk = 2;
					player.atk += 7;
					player.gold -= 150;
				}
				break;
		}
		return;
	}
}
//Only way to gain life in first area
void creepyLady(){	
	
	bool leave = false;
	
	cout << "You approach the counter of ragged shop.\nThe lady behind the counter shows you a goat heart\n"
			<<	"Do you buy the goats heart? (10g)\nCurrent gold: " << player.gold << std::endl << "(1)Yes/(2)No\n";
	
		int input;
		cin >> input;
		cout << endl;
	
	while(!leave){
																		//Below This comment is some numbers used to determine the amount of life the player is currently allowed to take
		if(input == 1 && player.gold >= 10 && player.maxHp < 10 + 3 * 5){
			player.maxHp += 5;
			player.currHp = player.maxHp;
			player.gold -= 10;
			player.item.potAmount = player.maxHp / 2;
			cout << "Your hp increased by 5!\n";
			cout << "Would you like to purchase another?\n(1)Y/(2)N\n";
			cin >> input;
			if(input == 2)
				leave = true;
		}
		else if(input == 1 && player.gold < 10){
			cout << "Insufficient funds\n";
			leave = true;
		}
		else {
			cout << "No hearts left to purchase\n";
			leave = true;
		}
	}
	return;
}
#endif