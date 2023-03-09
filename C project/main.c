#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"
#include "save.h"
#include "game.h"



struct deck *deck_hand, *player_hand = NULL, *dealer_hand = NULL;
int cash = 1000, pot = 0, player_score = 0;
char playing = 1, dealer_turn = 0;
char deck_len = 0, player_len = 0, dealer_len = 0; //since the deck is 52 cards, saving memory by using 1 byte for the length


int main()
{
	deck_hand = malloc(sizeof(struct deck));
	init_deck(deck_hand, &deck_len);
	srand(time(NULL));
//	print_deck_binary(deck_hand);
	cash = load_save();
	while (playing)
	{
		betting(&cash, &pot);
		draw_cards(&deck_hand, &player_hand, &deck_len, &player_len, 2);
		draw_cards(&deck_hand, &dealer_hand, &deck_len, &dealer_len, 2);
		player_score = player_round(&player_hand, dealer_hand, &deck_hand, &player_len, dealer_len, &deck_len, &cash, &pot);
		if (player_score > 0) //checks if the dealer needs to play
			dealer_round(player_hand, &dealer_hand, &deck_hand, player_len, &dealer_len, &deck_len, &cash, &pot, player_score);

		return_to_deck(&player_hand, &dealer_hand, &deck_hand, &dealer_len, &player_len, &deck_len);
		if (can_play(cash))
			playing = save_to_file(cash);
		else
			playing = 0;
	}
	free_deck(&deck_hand);
	return 0;
}