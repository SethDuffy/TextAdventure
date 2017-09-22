#include "GameLib.h"
#include "Combat.h"
#include "Markets.h"
#include <ctime>

using std::string;
using std::cin;
using std::cout;
using std::endl;

void town(void);
/*		 

Key:  ** == Update

TODO LIST

implement experience system **started implementation not even close to complete... need to rescale exp required for level up or
exp enemys give

implement monster loot drop system
implement later stages of enemys
implement other mob sections
implement some sort of boss for the first area

Separate Into Files **Separated some But Not all that I wanted to. encounter problems porting

*implement revive system ***Not Sure If That's The Direction I Want To Take This***
**Kind of implemented it with save system.
people can go back to previous spots. Will still 
keep this in mind
*/
//Global Variables seem to be something that is widely frowned upon. hopefully me of the future finds of a way to pass variables 
//More consistently by that I mean the amount of data that has to be supplied, versus the fact that these functions dont have the 
//correct scope 
//**Kind of Fixed it
Stats player;
Stats enemy;

void enemyDecl(){
	string names[] = {(string)"Bolvar, The Bad", (string)"Carl, The Threatening", (string)"Granny Smith", 
					  (string)"Balrog, The Stolen Name", (string)"Fictitious, The Non-Existent",
					  (string)"Valgar, The Named", (string)"Skeleton 1", (string)"Greeny, The Golbin"};

	//Give the enemy a randomly selected name
	enemy.name = names[(rand()%8)];
	enemy.maxHp = rand() % 9 + player.atk, enemy.atk = rand() % (player.maxHp / 4) + 1, 
	enemy.crit = rand() % (player.maxHp / 3) + 1, enemy.gold = enemy.maxHp + enemy.atk + enemy.crit, enemy.def = rand() % 2,
	enemy.exp = rand() % (enemy.maxHp - player.atk);

	if(player.area == 1){
		enemy.maxHp = clamp(5, 15, enemy.maxHp);
		enemy.atk = clamp(1, 3, enemy.atk);
		enemy.crit = clamp(1, 3, enemy.crit);
		enemy.exp = clamp(3, 500, enemy.exp);
	}
	enemy.currHp = enemy.maxHp;
	return;
}


void hospital(){
	cout << "A nurse approaches you\nYou Have " << player.gold << " gold\nWhat will you do\n(1)Heal(" 
		 << player.maxHp / 4 <<  "g)\n(2)Run Away(0g)\n";

	char input;
	cin >> input;
	cout << endl;
	if(input == '1' && player.gold >= (player.maxHp / 4)){
		player.currHp = player.maxHp;
		player.gold -= player.maxHp / 4;
		cout << "You were fully Healed\n";
	}
	else if(input == '2')
		return;
    else if(player.gold < player.maxHp / 4 && input == '1'){
        cout << "Insufficient funds\nYou Have " << player.gold << " gold\n";
    }
	else {
		hospital();
	}
	return;
}
void options(){
	cout << "(1)See Stats\n(2)Save Game\n(3)Leave\n";

	char input = getInput();

	switch (input){
		case '1' :
			displayStats();
			break;
		case '2' : 
			save();
			break;
        default :
            options();
            break;
	}
	return;
}
void levelUp(){
	if(player.exp >= player.nextLevel){

		player.level += 1;
		player.nextLevel = player.level * 10;
		player.exp = 0;

		cout << "\n\nYou levelled up to lv. " << player.level << "!\n"
		<< "You received ";

		int r = rand()%100;

		if(r < 5){

			cout << "Defence +1";

			player.def += 1;
		}
		else if(r >= 5 && r < 50){

			cout << "Potion +1";

			player.item.potion += 1;
		}
		else if(r >= 50 && r < 80){

			cout << "Attack Crystal +1";

			player.item.atkCrystal += 1;
		}
		else if(r >= 80 && r < 100){

			cout << "Defense Crystal +1";

			player.item.defCrystal += 1;
		}
		else
			cout << "Error selecting reward." << endl;
	}
	return;
}
void encounter(){ //logic for what happens if the player enters an encounter
	//sets stats for enemy
	enemyDecl();
	//displays stats of the player
	playerStatus();

	cout << "You encounter " << enemy.name << " what do you do?\n";

	while(player.currHp > 0 && enemy.currHp > 0){
		cout << "(1)Attack (2)Flee (3)Inventory\n";

		char input = getInput();

		if(input == '1'){
			attack(player.name, enemy.atk, player.currHp, enemy.crit, player.def);
			attack(enemy.name, player.atk, enemy.currHp, player.crit, enemy.def);
			playerStatus();
			enemyStatus();

		}
		else if(input == '2'){
			//If Flee Returns true return to town
			if(flee("enemy", player.atk, enemy.atk))
				return;
		}
		else if(input == '3'){
			Inventory();
		}
		else 
			encounter();
	}
	levelUp();
	if(enemy.currHp < 1 && player.currHp > 0){
		player.gold += enemy.gold;
		player.exp += enemy.exp;
	}
	death();
	return;
}
void town(){
	//Main hub for the player to navigate through
	cout << "You enter a small town\nWhere do you go?\n(1)Forest\n(2)Market\n(3)Hospital\n(4)Save\n(5)Options\n(6)End it all\n";

	char input = getInput();

	switch (input){
		case '1' : 
			encounter();
			break;
		case '2' :
			market1();
			break;
		case '3' :
			hospital();
			break;
		case '4' :
			save();
			break;
		case '5' :
			options();
			break;
		case '6' :
				player.currHp = 0;
				cout << "ded\n";
				break;
	}
	return;
}

/* NEED TO FIGURE OUT HOW TO MAKE A MORE PLIABLE SYSTEM FOR BATTLE AND ENEMYS  **Kind Of Did**  */
int main(){
	srand(time(NULL));

	cout << "\n(1)Load Old File?\n(2)Start New File?\n";

	char input = getInput();

	if(input == '2'){
   	 	player.maxHp = 10;
   	 	player.currHp = player.maxHp;
  		player.atk = 2;
   		player.crit = 2;
   	 	player.gold = 0;
   		player.area = 1;
   		player.level = 1;
   		player.exp = 0;
   		player.nextLevel = player.level * 10;
   	 	player.item.potion = 1;
   	 	player.item.potAmount = 5;
   	 	player.item.atkCrystal = 0;
   	 	player.item.defCrystal = 0;
   	 	player.item.buffAmount = 2;
   	 	playerStatus();

   	}
   	else if(input == '1')
   		loadSave();
   	else
   		main();
   	if(player.atk < 1){
   		cout << "No File Found\n";
   		main();
   	}
	do{
		town();
	}
	while(player.currHp > 0);

	return 0;
}











