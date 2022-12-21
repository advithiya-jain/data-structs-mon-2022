#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include "rbtree.h"

void initMaxValues(Node** set_max_values, int max_attr[10][2]) {
	int key, value;
	for (int i = 0; i < 10; i++) {
		key = max_attr[i][0];
		value = max_attr[i][1];
		insert(set_max_values, key, value);
	}
}

void initPlayerValues(Node** player_values, int max_attr[10][2]) {
	insert(player_values, 0, 1); // level
	insert(player_values, 1, 25); // health
	insert(player_values, 2, 0); // xp
	insert(player_values, 3, 6); // items
	for (int i = 4; i < 8; i++) {
		insert(player_values, i, max_attr[i][1]);
	}
	insert(player_values, 8, 5); // health pots
	insert(player_values, 9, 5); // repair pots
}

void welcome(char input, int deaths){

	printf("Welcome to this basic game, right now you have the current options available: \n");

	if (input == 'y' || input == 'Y') {
		printf("1. Tutorial\n");
		printf("2. View your stats\n");
		printf("3. Play the game!\n");
		printf("4. Exit\n");
		if (deaths > 0)	printf("5. View deaths\n");
	}
}

void tutorial(){
	printf("This is a basic game, you have 4 options to choose from, each option will have a different outcome.\n");
	printf("The options are: \n");
	printf("1. Fight a monster\n");
	printf("2. Rest\n");
	printf("3. Use an item\n");
	printf("\n When you fight a monster (monster health is always 200) you have multiple items to choose from,\n");
	printf("each item has a different outcome and have different durabilities, the items are: \n");
	printf("1. Sword (durability: 50, damage: 25)\n");
	printf("2. Claymore (durability: 100, damage: 50)\n");
	printf("3. Wand (durability: 15, damage: 100)\n");
	printf("4. Spear (durability: 25, damage: 75)\n");
	printf("5. Health potion (start with: 5)\n");
	printf("6. Repair potion (start with: 5)\n");
	printf("\nThe durability of each item decreases by 5 every time you use it.\n");
	printf("The durability of each item can never be less than 0. If it reaches 0 you will be unable to use that item\n");
	printf("until you repair it using a repair potion.\n");
	printf("\nThe health potion restores 50 health and the repair potion restores 10 durability. There is no limit to how many of these you can hold.\n");
	printf("Every time you defeat a monster you will gain 50 xp and 10 health. You also have a 40%% chance of getting 1 health potion as well as 1 repair potion.\n");
	printf("\nWhen you rest you will gain 25 health and no xp. You also have a 20%% chance of getting the 2 potions mentioned before.\n");
	printf("You can only rest once in between fighting monsters. You cannot rest while fighting a monster.\n");
	printf("\nThat's it! Type \'e\' or \'E\' to exit the game or anything else to go back to the main menu.\n");

}

void viewStats(Node* player_values){
	printf("Level: %d\n", search(player_values, 0)->value);
	printf("Health: %d\n", search(player_values, 1)->value);
	printf("XP: %d\n", search(player_values, 2)->value);
	printf("Items: %d\n", search(player_values, 3)->value);
	printf("	- Sword durability: %d\n", search(player_values, 4)->value);
	printf("	- Claymore durability: %d\n", search(player_values, 5)->value);
	printf("	- Wand durability: %d\n", search(player_values, 6)->value);
	printf("	- Spear durability: %d\n", search(player_values, 7)->value);
	printf("	- Health potions: %d\n", search(player_values, 8)->value);
	printf("	- Repair potions: %d\n", search(player_values, 9)->value);
	printf("Enter Choice: 1. Fight, 2. Rest, 3. Use item, 4. Exit\n");
}

int main(int argc, char** argv) {
	
	// Initialising the 2 "dictionaries" to be used
	
	// dictionary to store the maximum values of each attribute: level, health, xp, items, item durability, etc.
	Node* set_max_values = NULL; 
	// dictionary to store the player's values of each attribute
	Node* player_values = NULL;
	int key, value;

	// Initialising the max keys and values of each attribute using the set_max_values dictionary and an temp array for insertion.

	//array layotu: { {key, value}, {key, value}, ... }
	// 0: level, 1: health, 2: xp, 3: items, 4: sword durability, 5: claymore durability, 6: wand durability, 7: spear durability
	// 8: health potion effect, 9: repair potion effect
	int max_attr[10][2] = {{0, 100}, {1, 500}, {2, 100}, {3, 6}, {4, 50}, {5, 100}, {6, 15}, {7, 25}, {8, 50}, {9, 10}};

	initMaxValues(&set_max_values, max_attr);

	// Initialising the player's values of each attribute using the player_values dictionary 
	initPlayerValues(&player_values, max_attr);

	int deaths = 0;
	int flag = 0;
	char input = 'y';
	int choice;
	
	do {
		Node* temp = search(player_values, 1);
		if (temp->value <= 0) {
			deaths++;
			printf("You died! Would you like to restart the game? (y/n)\n");
			scanf("%c", &input);
			if (input == 'y') {
				flag = 0;
				// reset player values
				initPlayerValues(&player_values, max_attr);
			}
			else {
				printf("Thank you for playing!\n");
				flag = 1;
				freeTree(&player_values);
				freeTree(&set_max_values);
				exit(0);
			}
		}
		else {
			welcome(input, deaths);
		}
	}while (flag == 0);

	
 
}