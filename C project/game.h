#ifndef GAME_H
#define GAME_H

#include "main.h"

#define IGNORE_LAST 1
#define ALLOW_LAST 0

int can_play(int cash);
void betting(int* cash, int* pot);
void print_hand(struct deck* hand, char len, char last);
void print_player(struct deck* dealer, struct deck* player, char dealer_len, char player_len);
void print_dealer(struct deck* dealer, struct deck* player, char dealer_len, char player_len);
int player_round(struct deck** player_hand, struct deck* dealer_hand, struct deck** deck_hand, char* player_len, char dealer_len, char* deck_len, int* cash, int* pot);
void dealer_round(struct deck* player_hand, struct deck** dealer_hand, struct deck** deck_hand, char player_len, char* dealer_len, char* deck_len, int* cash, int* pot, int player_score);


#endif