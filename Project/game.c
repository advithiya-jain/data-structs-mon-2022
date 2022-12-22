#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rbtree.h"
#include "gamefns.h"

// Initialising the max vaalue dictionariy to be used
// Stores the maximum values of each attribute: level, health, xp, items, item durability, etc.
Node *set_max_values = NULL;

// Initialising the max keys and values of each attribute using the set_max_values dictionary and an temp array for insertion.

// array layotu: { {key, value}, {key, value}, ... }
//  0: level, 1: health, 2: xp, 3: items, 4: sword durability, 5: claymore durability, 6: wand durability, 7: spear durability
//  8: health potion effect, 9: repair potion effect, 10: monster health
int max_attr[11][2] = {{0, 100}, {1, 300}, {2, 100}, {3, 6}, {4, 50}, {5, 100}, {6, 15}, {7, 25}, {8, 50}, {9, 10}, {10, 200}};

/**
 * ! Function for battling
 * @param player_values is the tree containing the player's values
 * @param set_max_values is the tree containing the max values
 * @param deaths is the number of deaths
 */
void fight_monster(Node **player_values, Node *set_max_values, int *rest) {
	int opt, miss = 0;
	int sword_dur, claymore_dur, wand_dur, spear_dur, health_pots, health, repair_pots, weapon_dur;
	char *input = malloc(sizeof(char) * 10);
	// check for death
	if (isDead(player_values)) {
		printf("You died. Thank you for playing the game!\n");
		exit(0);
	}
	// check if monster has been defeated
	if (search(player_values, 10)->value <= 0) {
		*rest = 0; // make the rest variable 0, indicating the player can rest again.
		printf("You have defeated the monster!\n");
		// update the player's values
		int xp = search(player_values, 2)->value;
		int health = search(player_values, 1)->value;
		xp = xp + 50;
		// level up mechanism
		if (xp >= search(&set_max_values, 2)->value) {
			update(player_values, 0, (search(player_values, 0)->value + 1)); // level up
			update(player_values, 2, 0);									 // reset xp
		}
		else update(player_values, 2, xp); // only update xp if not >= max xp
		update(player_values, 1, health + 10);
		int level = search(player_values, 0)->value;
		int monster_health = search(&set_max_values, 10)->value + (level * 25);
		update(player_values, 10, monster_health);
		// random 40% chance of gaining items
		if (randomiser(40)) {
			int health_pots = search(player_values, 8)->value;
			update(player_values, 8, health_pots + 1);
			printf("You have gained 1 health potion!\n");
		}
		if (randomiser(40)) {
			int repair_pots = search(player_values, 9)->value;
			update(player_values, 9, repair_pots + 1);
			printf("You have gained 1 repair potion!\n");
		}
		base_game(player_values, set_max_values, rest);
	}
	printf("\nMonster Health: %d\n", search(player_values, 10)->value);
	printf("Your Health: %d\n", search(player_values, 1)->value);
	printf("Please enter your option:\n");
	printf("1. Sword\n");
	printf("2. Claymore\n");
	printf("3. Wand\n");
	printf("4. Spear\n");
	printf("5. Health potion\n");
	printf("6. Repair potion\n");
	printf("7. View your stats\n");
	printf("8. Exit\n\n");
	scanf("%s", input);
	opt = atoi(input);
	switch (opt) {

		case 1: // fighting with sword
				sword_dur = search(player_values, 4)->value;
				if (sword_dur <= 0) {
					printf("Your sword is broken, you cannot use it!\n");
					fight_monster(player_values, set_max_values, rest);
				}
				if (randomiser(50)) {
					int mon_health = search(player_values, 10)->value;
					update(player_values, 10, mon_health - 25);
					update(player_values, 4, sword_dur - 10);
					printf("You hit the monster with your sword and dealt 25 damage!\n");
					miss = 0;
					fight_monster(player_values, set_max_values, rest);
				}
				else {
					printf("You missed the monster!\n");
					miss = 1;
				}
				break;

		case 2: // fighting with claymore
				claymore_dur = search(player_values, 5)->value;
				if (claymore_dur <= 0) {
					printf("Your claymore is broken, you cannot use it!\n");
					fight_monster(player_values, set_max_values, rest);
				}
				if (randomiser(35)) {
					int mon_health = search(player_values, 10)->value;
					update(player_values, 10, mon_health - 50);
					update(player_values, 5, claymore_dur - 10);
					printf("You hit the monster with your claymore and dealt 50 damage!\n");
					miss = 0;
					fight_monster(player_values, set_max_values, rest);
				}
				else {
					printf("You missed the monster!\n");
					miss = 1;
				}
				break;

		case 3: // fighting with wand
				wand_dur = search(player_values, 6)->value;
				if (wand_dur <= 0) {
					printf("Your wand is broken, you cannot use it!\n");
					fight_monster(player_values, set_max_values, rest);
				}
				if (randomiser(75)) {
					int mon_health = search(player_values, 10)->value;
					update(player_values, 10, mon_health - 100);
					update(player_values, 6, wand_dur - 10);
					printf("You hit the monster with your wand and dealt 100 damage!\n");
					miss = 0;
					fight_monster(player_values, set_max_values, rest);
				}
				else {
					printf("You missed the monster!\n");
					miss = 1;
				}
				break;

		case 4: // fighting with spear
				spear_dur = search(player_values, 7)->value;
				if (spear_dur <= 0) {
					printf("Your spear is broken, you cannot use it!\n");
					fight_monster(player_values, set_max_values, rest);
				}
				if (randomiser(80)) {
					int mon_health = search(player_values, 10)->value;
					update(player_values, 10, mon_health - 20);
					update(player_values, 7, spear_dur - 10);
					printf("You hit the monster with your spear and dealt 20 damage!\n");
					miss = 0;
					fight_monster(player_values, set_max_values, rest);
				}
				else {
					printf("You missed the monster!\n");
					miss = 1;
				}
				break;

		case 5: // using health potion
				health_pots = search(player_values, 8)->value;
				if (health_pots <= 0) {
					printf("You have no health potions, you cannot use it!\n");
					fight_monster(player_values, set_max_values, rest);
				}

				health = search(player_values, 1)->value;
				health += 50;
				if (health > 300)  health = search(&set_max_values, 1)->value;
				update(player_values, 1, health);
				update(player_values, 8, health_pots - 1);
				printf("You have used a health potion and healed 50 health!\n");
				break;

		case 6: // using repair potion
				repair_pots = search(player_values, 9)->value;
				if (repair_pots <= 0) {
					printf("You have no repair potions, you cannot use it!\n");
					fight_monster(player_values, set_max_values, rest);
				}
				for (int i = 4; i < 8; i++) {
					weapon_dur = search(player_values, i)->value;
					weapon_dur += 20;
					if (weapon_dur > search(&set_max_values, i)->value)  weapon_dur = search(&set_max_values, i)->value;
					update(player_values, i, weapon_dur);
				}
				update(player_values, 9, repair_pots - 1);
				printf("You have used a repair potion and repaired all your weapons!\n");

				break;

		case 7: // view stats
				viewStats(*player_values);
				fight_monster(player_values, set_max_values, rest);
				break;

		case 8: // exit to base game
				printf("Exiting battle...\n");
				base_game(player_values, set_max_values, rest);
				break;

		default: // invalid case
				printf("Invalid option, please try again\n");
				fight_monster(player_values, set_max_values, rest);
				break;
	}

	// check for death
	if (isDead(player_values))  death();
	// If you miss and the monster hits you, you take damage
	if (miss == 1) {
		int level = search(player_values, 0)->value;
		int damage = (level * 20) + 5; // calculate damage based on level
		int health = search(player_values, 1)->value;
		update(player_values, 1, health - damage); // update health
		printf("The monster has hit you for %d damage!\n", damage);
		// check for death
		if (isDead(player_values)) {
			death();
		}
		else  fight_monster(player_values, set_max_values, rest);
	}

	// check if monster is dead
	else if (search(player_values, 10)->value <= 0) {
		*rest = 0; // reset rest
		printf("You have defeated the monster!\n");
		// update values as done eariler.
		int xp = search(player_values, 2)->value;
		int health = search(player_values, 1)->value;
		xp = xp + 50;
		if (xp >= search(&set_max_values, 2)->value) {
			update(player_values, 0, (search(player_values, 0)->value + 1));
			update(player_values, 2, 0);
		}
		else  update(player_values, 2, xp);
		update(player_values, 1, health + 10);
		int level = search(player_values, 0)->value;
		int monster_health = search(&set_max_values, 10)->value + (level * 25);
		update(player_values, 10, monster_health);
		if (randomiser(40)) {
			int health_pots = search(player_values, 8)->value;
			update(player_values, 8, health_pots + 1);
			printf("You have gained 1 health potion!\n");
		}
		if (randomiser(40)) {
			int repair_pots = search(player_values, 9)->value;
			update(player_values, 9, repair_pots + 1);
			printf("You have gained 1 repair potion!\n");
		}
		base_game(player_values, set_max_values, rest);
	}
	// if monster is not dead, continue fighting
	else
		fight_monster(player_values, set_max_values, rest);
}

/**
 * ! Function for the base game / main menu
 * @param player_values is the tree containing the player's values
 * @param set_max_values is the tree containing the max values
 * @param deaths is the number of deaths
 */
void base_game(Node **player_values, Node *set_max_values, int *rest)
{
	int opt;
	char *input = malloc(10 * sizeof(char));
	if (isDead(player_values))  death();
	
	printf("\nPlease enter your option:\n");
	printf("1. Fight a monster\n");
	printf("2. Rest\n");
	printf("3. View your stats\n");
	printf("4. Exit\n\n");
	scanf("%s", input);
	opt = atoi(input);
	switch (opt)
	{
	case 1:	fight_monster(player_values, set_max_values, rest);
			if (isDead(player_values)) death(); // check if player is dead
			break;

	case 2: // if player has not rested yet
			if (*rest == 0) {
				int health = search(player_values, 1)->value;
				update(player_values, 1, health +25); // add 10 health
				printf("You have rested and healed 10 health!\n");
				*rest = 1;
			}
			else  printf("You have already rested!\n");

			base_game(player_values, set_max_values, rest);
			break;

	case 3:
			viewStats(*player_values);
			base_game(player_values, set_max_values, rest);
			break;

	case 4:
			printf("Exiting... Thank you for playing!\n");
			exit(0);
			break;
	default:
			printf("Invalid option, please try again\n");
			base_game(player_values, set_max_values, rest);
			break;
	}
}

/**
 * ! Main function for the game
 */
int main(int argc, char **argv)
{

	srand(time(NULL)); // seed for randomiser
	// dictionary to store the player's values of each attribute
	Node *player_values = NULL;

	initMaxValues(&set_max_values, max_attr);

	// Initialising the player's values of each attribute using the player_values dictionary
	initPlayerValues(&player_values, max_attr);

	int flag = 0;
	char *input = (char *)malloc(50 * sizeof(char));
	int choice;
	int rest = 0;

	// do while loop that runs the game until the user dies, or exits
	do {
		Node *temp = search(&player_values, 1); // base case
		if (temp->value <= 0)  death();
		
		// if the player is not dead, the game will continue
		else {
			// print the welcome message
			welcome();
			printf("Enter your choice: ");
			scanf("%s", input);
			choice = atoi(input);
			switch (choice) {

			case 1:
				tutorial(); // prints the tutorial
				break;

			case 2:
				viewStats(player_values); // prints the player's stats
				break;

			case 3: // starts the game
				base_game(&player_values, set_max_values, &rest);
				// check for death after the game
				if (isDead(&player_values)) death();
				break;

			case 4:
				printf("Thank you for playing!\n"); // exit case
				flag = 1;
				freeTree(&player_values);
				freeTree(&set_max_values);
				exit(0);
				break;
			default:
				printf("Invalid input, please try again.\n");
				break;
			}
		}
	} while (flag == 0);

	return 0;
}