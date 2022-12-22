#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include "rbtree.h"
#include "gamefns.h"

// Initialising the max vaalue dictionariy to be used
// Stores the maximum values of each attribute: level, health, xp, items, item durability, etc.
Node* set_max_values = NULL; 

// Initialising the max keys and values of each attribute using the set_max_values dictionary and an temp array for insertion.

//array layotu: { {key, value}, {key, value}, ... }
// 0: level, 1: health, 2: xp, 3: items, 4: sword durability, 5: claymore durability, 6: wand durability, 7: spear durability
// 8: health potion effect, 9: repair potion effect, 10: monster health
int max_attr[11][2] = {{0, 100}, {1, 300}, {2, 100}, {3, 6}, {4, 50}, {5, 100}, {6, 15}, {7, 25}, {8, 50}, {9, 10}, {10, 200}};

void fight_monster(Node** player_values, Node* set_max_values, int* deaths) {
    int opt, miss = 0;
    int sword_dur, claymore_dur, wand_dur, spear_dur, health_pots, health, repair_pots, weapon_dur;

    if(isDead(player_values)) {
        *deaths++; return;
    }
    printf("Monster Health: %d\n", search(player_values, 10)->value);
    printf("Please enter your option:\n");
    printf("1. Sword\n");
    printf("2. Claymore\n");
    printf("3. Wand\n");
    printf("4. Spear\n");
    printf("5. Health potion\n");
    printf("6. Repair potion\n");
    printf("7. View your stats\n");
    printf("8. Exit\n\n");
    scanf("%d", &opt);
    switch (opt) {

        case 1: 
                sword_dur = search(player_values, 4)->value;
                if(sword_dur <= 0) {
                    printf("Your sword is broken, you cannot use it!\n");
                    fight_monster(player_values, set_max_values, deaths);
                }
                if (randomiser(50)) {
                    int mon_health = search(player_values, 10)->value;
                    update(player_values, 10, mon_health - 25);
                    update(player_values, 4, sword_dur - 10);
                    printf("You hit the monster with your sword and dealt 25 damage!\n");
                    miss = 0;
					fight_monster(player_values, set_max_values, deaths);

                }
                else {
                    printf("You missed the monster!\n");
                    miss = 1;
                }
                break;

        case 2: claymore_dur = search(player_values, 5)->value;
                if(claymore_dur <= 0) {
                    printf("Your claymore is broken, you cannot use it!\n");
                    fight_monster(player_values, set_max_values, deaths);
                }
                if (randomiser(35)) {
                    int mon_health = search(player_values, 10)->value;
                    update(player_values, 10, mon_health - 50);
                    update(player_values, 5, claymore_dur - 10);
                    printf("You hit the monster with your claymore and dealt 50 damage!\n");
                    miss = 0;
					fight_monster(player_values, set_max_values, deaths);
                }
                else {
                    printf("You missed the monster!\n");
                    miss = 1;
                }
                break;
        case 3: wand_dur = search(player_values, 6)->value;
                if(wand_dur <= 0) {
                    printf("Your wand is broken, you cannot use it!\n");
                    fight_monster(player_values, set_max_values, deaths);
                }
                if (randomiser(75)) {
                    int mon_health = search(player_values, 10)->value;
                    update(player_values, 10, mon_health - 100);
                    update(player_values, 6, wand_dur - 10);
                    printf("You hit the monster with your wand and dealt 100 damage!\n");
                    miss = 0;
					fight_monster(player_values, set_max_values, deaths);

                }
                else {
                    printf("You missed the monster!\n");
                    miss = 1;
                }
                break;
        case 4: spear_dur = search(player_values, 7)->value;
                if(spear_dur <= 0) {
                    printf("Your spear is broken, you cannot use it!\n");
                    fight_monster(player_values, set_max_values, deaths);
                }
                if (randomiser(80)) {
                    int mon_health = search(player_values, 10)->value;
                    update(player_values, 10, mon_health - 20);
                    update(player_values, 7, spear_dur - 10);
                    printf("You hit the monster with your spear and dealt 20 damage!\n");
                    miss = 0;
					fight_monster(player_values, set_max_values, deaths);

                }
                else {
                    printf("You missed the monster!\n");
                    miss = 1;
                }
                break;

        case 5: health_pots = search(player_values, 8)->value;
                if(health_pots <= 0) {
                    printf("You have no health potions, you cannot use it!\n");
                    fight_monster(player_values, set_max_values, deaths);
                }
                
                health = search(player_values, 1)->value;
				health += 50;
				if(health > 300) health = search(set_max_values, 1)->value;
                update(player_values, 1, health);
                update(player_values, 8, health_pots - 1);
                printf("You have used a health potion and healed 50 health!\n");
                break;

        case 6: repair_pots = search(player_values, 9)->value;
                if(repair_pots <= 0) {
                    printf("You have no repair potions, you cannot use it!\n");
                    fight_monster(player_values, set_max_values, deaths);
                }
				for (int i = 4; i < 8; i++) {
					weapon_dur = search(player_values, i)->value;
					weapon_dur += 20;
					if(weapon_dur > search(set_max_values, i)->value) {
						weapon_dur = search(set_max_values, i)->value;
					}
					update(player_values, i, weapon_dur);
				}
                update(player_values, 9, repair_pots - 1);
                printf("You have used a repair potion and repaired all your weapons!\n");

            	break;

        case 7:	viewStats(*player_values);
            	fight_monster(player_values, set_max_values, deaths);
            	break;

        case 8: printf("Exiting battle...\n");
            	base_game(player_values, set_max_values, deaths);
            	break;
		
        default:
            printf("Invalid option, please try again\n");
            fight_monster(player_values, set_max_values, deaths);
            break;
    }

    health = search(player_values, 1)->value;
    if(health <= 0){
            *deaths++;
            base_game(player_values, set_max_values, deaths);
        }
    
    if (miss == 1) {
        update(player_values, 1, health - 25);
        printf("The monster has hit you for 25 damage!\n");
        health = search(player_values, 1)->value;
        if(health <= 0){
            *deaths++;
            base_game(player_values, set_max_values, deaths);
        }
        else fight_monster(player_values, set_max_values, deaths);
    }

    else if(search(player_values, 10)->value <= 0){
        printf("You have defeated the monster!\n");
        int xp = search(player_values, 2)->value;
        int health = search(player_values, 1)->value;
        update(player_values, 2, xp + 50);
        update(player_values, 1, health + 10);
        update(player_values, 10, 200);
        if(randomiser(40)){
            int health_pots = search(player_values, 8)->value;
            update(player_values, 8, health_pots + 1);
            printf("You have gained 1 health potion!\n");
        }
        if(randomiser(40)){
            int repair_pots = search(player_values, 9)->value;
            update(player_values, 9, repair_pots + 1);
            printf("You have gained 1 repair potion!\n");
        }
        base_game(player_values, set_max_values, deaths);
    }
    else fight_monster(player_values, set_max_values, deaths);
}

void base_game(Node** player_values, Node* set_max_values, int* deaths) {
    int opt; int rest = 0;
    if(isDead(player_values)) {
		*deaths++; return;
	}

    printf("Please enter your option:\n");
    printf("1. Fight a monster\n");
    printf("2. Rest\n");
    printf("3. View your stats\n");
    printf("4. Exit\n\n");
    scanf("%d", &opt);
    switch (opt) {
        case 1: fight_monster(player_values, set_max_values, deaths);
                if (isDead(player_values)) return;
                break;

        case 2: if(rest == 0){
                    int health = search(player_values, 1)->value;
                    update(player_values, 1, health + 10);
                    printf("You have rested and healed 10 health!\n");
                    rest = 1;
                }
                else printf("You have already rested!\n");
            break;

        case 3: viewStats(*player_values);
                base_game(player_values, set_max_values, deaths);
                break;
        case 4:
            printf("Exiting to main menu...\n");
            return;
            break;
        default:
            printf("Invalid option, please try again\n");
            base_game(player_values, set_max_values, deaths);
            break;
    }
    
}

int main(int argc, char** argv) {

	srand(time(NULL)); // seed for randomiser
	// dictionary to store the player's values of each attribute
	Node* player_values = NULL;

	initMaxValues(&set_max_values, max_attr);

	// Initialising the player's values of each attribute using the player_values dictionary 
	initPlayerValues(&player_values, max_attr);

	int deaths = 0;
	int flag = 0;
	char* input = (char*)malloc(50*sizeof(char));
	int choice;
	
	do {
		Node* temp = search(&player_values, 1);
		if (temp->value <= 0) {
			deaths++;
			printf("You died! Would you like to restart the game? (1 = yes/ anything else = no)\n");
			scanf("%s", &input);
			if (input == 'y') {
				flag = 0;
				// reset player values
				initPlayerValues(&player_values, max_attr);
				continue;
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
			printf("Enter your choice: ");
			scanf("%d", &choice);

			switch (choice) {
				case 1:
					tutorial();
					break;
				case 2: viewStats(player_values);
						break;
				case 3: base_game(&player_values, set_max_values, &deaths);
						break;

				case 4: printf("Thank you for playing!\n");
						flag = 1;
						freeTree(&player_values);
						freeTree(&set_max_values);
						exit(0);
						break;

				case 5: printf("You have died %d times.\n", deaths);
						break;
				default:
					printf("Invalid input, please try again.\n");
					break;
			}
		}
	}while (flag == 0);
 
}