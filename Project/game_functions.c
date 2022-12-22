#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include "rbtree.h"
#include "gamefns.h"

/**
 * ! Function to check if the player is dead
 * @param player_values is the tree containing the player's values
*/
bool isDead(Node** player_values){
    int health = search(player_values, 1)->value;
    if (health <= 0) {
        return true;
    }
    return false;
}

/**
 * ! Function to initialise the max values of the player
 * @param set_max_values is the tree to be initialised
 * @param max_attr is the array containing the max values
*/
void initMaxValues(Node** set_max_values, int max_attr[11][2]) {
	int key, value;
	for (int i = 0; i < 11; i++) {
		key = max_attr[i][0];
		value = max_attr[i][1];
		insert(set_max_values, key, value);
	}
}

/**
 * ! Function to initialise the player's values
 * @param player_values is the tree to be initialised
 * @param max_attr is the array containing the max values
*/
void initPlayerValues(Node** player_values, int max_attr[11][2]) {
	insert(player_values, 0, 1); // level
	insert(player_values, 1, 300); // health
	insert(player_values, 2, 0); // xp
	insert(player_values, 3, 6); // items
	for (int i = 4; i < 8; i++) {
		insert(player_values, i, max_attr[i][1]);
	}
	insert(player_values, 8, 5); // health pots
	insert(player_values, 9, 5); // repair pots
    insert(player_values, 10, 200); // monster health
}

/**
 * ! Function to print the welcome message
 * @param input is the input from the user
*/
void welcome(){

	printf("Welcome to this basic game, right now you have the current options available: \n");
    printf("1. Tutorial\n");
    printf("2. View your stats\n");
    printf("3. Play the game!\n");
    printf("4. Exit\n");
}

/**
 * ! Function to print the tutorial
*/
void tutorial(){
	printf("This is a basic game, you have 4 options to choose from, each option will have a different outcome.\n");
	printf("The options are: \n");
	printf("1. Fight a monster\n");
	printf("2. Rest\n");
    printf("3. View your stats\n");
	printf("4. Exit\n");
	printf("\n When you fight a monster (monster health is always 200) you have multiple items to choose from,\n");
	printf("each item has a different outcome and have different durabilities, the items are: \n");
	printf("1. Sword (durability: 50, damage: 25, chance: 50%%)\n");
	printf("2. Claymore (durability: 100, damage: 50, chance: 35%%)\n");
	printf("3. Wand (durability: 15, damage: 100, chance: 75%%)\n");
	printf("4. Spear (durability: 25, damage: 20, chance: 80%%)\n");
	printf("5. Health potion (start with: 5)\n");
	printf("6. Repair potion (start with: 5)\n");
	printf("\nThe durability of each item decreases by 5 every time you use it.\n");
	printf("The durability of each item can never be less than 0. If it reaches 0 you will be unable to use that item\n");
	printf("until you repair it using a repair potion.\n");
	printf("\nThe health potion restores 50 health and the repair potion restores 10 durability. There is no limit to how many of these you can hold.\n");
	printf("Every time you defeat a monster you will gain 50 xp and 10 health. You also have a 40%% chance of getting 1 health potion as well as 1 repair potion.\n");
	printf("\nWhen you rest you will gain 25 health and no xp. There is no limit to your health.\n");
	printf("You can only rest once in between fighting monsters. You cannot rest while fighting a monster.\n");
    printf("\nWhen you use an item you will have a chance of winning the fight, if you win you will gain 50 xp and 10 health.\n");
    printf("You will level up if your xp reaches 100. When you level up, the monsters you encounter will gain more health and will be harder to defeat.\n");
    printf("So use your items wisely!\n");
    printf("\nYou can view your stats at any time by pressing 3. If your health reaches 0 you die and the game will end.\n");
	printf("\nThat's it! Enter any character(s) to go back to the main menu\n\n");
    scanf("%*s");

}

/**
 * ! Function to print the player's stats
 * @param player_values is the tree containing the player's values
*/
void viewStats(Node* player_values){
	printf("\nLevel: %d\n", search(&player_values, 0)->value);
	printf("Health: %d\n", search(&player_values, 1)->value);
	printf("XP: %d\n", search(&player_values, 2)->value);
	printf("Items: %d\n", search(&player_values, 3)->value);
	printf("	- Sword durability: %d\n", search(&player_values, 4)->value);
	printf("	- Claymore durability: %d\n", search(&player_values, 5)->value);
	printf("	- Wand durability: %d\n", search(&player_values, 6)->value);
	printf("	- Spear durability: %d\n", search(&player_values, 7)->value);
	printf("	- Health potions: %d\n", search(&player_values, 8)->value);
	printf("	- Repair potions: %d\n", search(&player_values, 9)->value);
	printf("\nEnter any character(s) to go back\n\n");
    scanf("%*s");

}

/**
 * ! Function that results a true result if the random number is less than or equal to the chance
 * * The random number is between 1 and 100
 * @param chance is % chance that is required, must be between 1 and 100
*/
bool randomiser(int chance){
    int random = rand() % 100 + 1;
    if (random <= chance) return true;
    else return false;
}

void death(){
    printf("You died. Thank you for playing the game!\n");
    exit(0);
}