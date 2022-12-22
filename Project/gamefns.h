#ifndef GAMEFNS_H
#define GAMEFNS_H
#include "rbtree.h"

void initMaxValues(Node** set_max_values, int max_attr[11][2]);
void initPlayerValues(Node** player_values, int max_attr[11][2]);
void welcome(char input, int deaths);
void tutorial();
void viewStats(Node* player_values);
void playGame(Node** player_values, int* deaths);
void fightMonster(Node** player_values, Node* set_max_values, int* deaths);
void base_game(Node** player_values, Node* set_max_values, int* deaths);
bool isDead(Node** player_values);
bool randomiser(int chance);

#endif