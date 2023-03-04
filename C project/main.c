#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "save.h"
#include "game.h"


struct deck* deck_hand, player_hand, dealer_hand;
int cash = 1000, pot = 0;
FILE save;

int main()
{
	deck_hand = malloc(sizeof(struct deck));
	init_deck(deck_hand);
	print_deck(deck_hand);
	pot = load_save(&save);

	free_deck(deck_hand);
	return 0;
}