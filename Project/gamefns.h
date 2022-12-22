#ifndef GAMEFNS_H
#define GAMEFNS_H
#include "rbtree.h"

void initMaxValues(Node** set_max_values, int max_attr[11][2]);
void initPlayerValues(Node** player_values, int max_attr[11][2]);
void welcome();
void tutorial();
void viewStats(Node* player_values);
void fightMonster(Node** player_values, Node* set_max_values, int* rest);
void base_game(Node** player_values, Node* set_max_values, int* rest);
bool isDead(Node** player_values);
void death();
bool randomiser(int chance);

#endif