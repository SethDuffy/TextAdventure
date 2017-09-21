#ifndef	_COMBAT_
#define _COMBAT_
#include "GameLib.h"


//calculates the damage an attack does
void attack(const string name, const int atk, int &enemyHp, const int critMult, const int def){

	int crit = atk * critMult;

	if((rand() % 10 + 1) > 2){
		enemyHp -= (atk - def);
		cout << name << " took " << atk - def << " damage\n";
	}
	else {
		enemyHp -= (crit - def);
		cout << name << " took " << crit - def << " damage\n";
	}
	return;
}
//Calculates players flee chances **player unable to flee if lower atk than attacker
bool flee(const string name, const int plyatk, const int enyatk){
	if(player.atk >= enemy.atk){
		if((rand() % player.atk) >= 1){
			cout << "You succefully fled from " << enemy.name << std::endl;
			return true;
		}
		else {
			cout << "You attempted to flee unsucessfully\n";
			player.currHp -= enemy.atk;
			cout << "You lost " << enemy.atk << " health\n";
			return false;
		}
	}	
	else {
		cout << "You can't flee from enemys stronger than you\n";
	}
	return false;

}
void death(){ //Repeatable death tracker
	if(player.currHp <= 0 && !(enemy.currHp <= 0))
		cout << "\n\nYou Lost\n";
	else if(enemy.currHp <= 0 && !(player.currHp <= 0))
		cout << "\n\nYou slayed " << enemy.name << " and\nGained " << enemy.gold << " gold and " << enemy.exp << " xp!\n";
	else
		cout << "\n\nYou Neither Won Nor Lost.\n";
}
void Inventory(){
	cout << "You have\n" << player.item.potion << " potion(s)           (1)\n"
		 << player.item.atkCrystal << 			  " attack crystal(s)   (2)\n"
		 << player.item.defCrystal << 			  " defense crystal(s)  (3)\n"
		 << 									  "Leave                 (4)\n";

	int input;
	cin >> input;

	switch (input) {
		case 1 :
			if(player.item.potion){
				int temp = player.currHp;
				player.item.potion -= 1;
				player.currHp += player.item.potAmount;
				player.currHp = clamp(0, player.maxHp, player.currHp);
				cout << "\nYou gained " << player.currHp - temp << " hp\n";
				attack(player.name, enemy.atk, player.currHp, enemy.crit, player.def);
			}
			break;
		case 2 :
			if(player.item.atkCrystal){
				player.atk += player.item.buffAmount;
				player.item.atkCrystal -= 1;
				cout << "\nYour attack was raised by " << player.item.buffAmount << " for a single combat phase" << endl;
				attack(player.name, enemy.atk, player.currHp, enemy.crit, player.def);
				attack(enemy.name, player.atk, enemy.currHp, player.crit, enemy.def);
				player.atk -= player.item.buffAmount;
				}
			break;
		case 3 :
			if(player.item.defCrystal){
				player.def += player.item.buffAmount;
				player.item.defCrystal -= 1;
				cout << "\nYour defense was raised by " << player.item.buffAmount << " for a single combat phase" << endl;
				attack(player.name, enemy.atk, player.currHp, enemy.crit, player.def);
				attack(enemy.name, player.atk, enemy.currHp, player.crit, enemy.def);
				player.def -= player.item.buffAmount;
				}
			break;
		default :
			break;
	}
	return;

}
#endif