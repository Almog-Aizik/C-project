#ifndef CARDS_H
#define CARDS_H

#include "main.h"

#define SUIT_MASK 0x0F
#define VALUE_MASK 0xF0

struct deck {
	unsigned char card;
	struct deck* next;
};

void init_deck(struct deck* head, char* len);
void free_deck(struct deck** head);
void draw_cards(struct deck** deck, struct deck** hand, char* deck_len, char* hand_len, int times);
void print_card(struct deck* hand, char card);
void move_all_cards(struct deck** hand, struct deck** target);
void return_to_deck(struct deck** player, struct deck** dealer, struct deck** deck, char* player_len, char* dealer_len, char* deck_len);
int check_score(struct deck** hand);

#endif