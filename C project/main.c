#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"
#include "save.h"
#include "game.h"



struct deck *deck_hand, *player_hand = NULL, *dealer_hand = NULL;
int cash = 1000, pot = 0;
char playing = 1, deck_len = 0, player_len = 0, dealer_len = 0; //since the deck is 52 cards, saving memory by using 1 byte for the length


int main()
{
	srand(time(NULL));
	deck_hand = malloc(sizeof(struct deck));
	//player_hand = malloc(sizeof(struct deck));
	//dealer_hand = malloc(sizeof(struct deck));
	init_deck(deck_hand, &deck_len);
//	print_deck_binary(deck_hand);
//	cash = load_save();
	while (playing && can_play(cash))
	{
		//cash = betting(&cash, &pot);
		draw_cards(&deck_hand, &player_hand, &deck_len, &player_len, 2); // needs a fix
		draw_cards(&deck_hand, &dealer_hand, &deck_len, &dealer_len, 2);
		print_player(dealer_hand, player_hand, dealer_len, player_len);
		
		playing = 0;
	}


	free_deck(deck_hand);
	return 0;
}