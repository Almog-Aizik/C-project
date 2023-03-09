#include <stdio.h>

#define IGNORE_LAST 1
#define ALLOW_LAST 0


int can_play(int cash);
int betting(int cash, int pot);
int print_hand(struct deck *hand, char len, char status);
int print_player(struct deck* dealer, struct deck* player, char dealer_len, char player_len);
int player_round(struct deck** player_hand, char* player_len, char* player_turn, char* cash, char* pot);
int dealer_round(struct deck* player_hand, struct deck** dealer_hand, struct deck** deck_hand, char player_len, char* dealer_len, int* deck_len, int* cash, int* pot, int player_score);

int can_play(int cash)
{
	if (cash >= 10)
		return 1;
	else
		return 0;
}

betting(int *cash, int *pot)
{
	int user_input = 0;
	printf("You have $%d\n", *cash);
	printf("\n How much would you like to bet? (must be a multiple of 10)\n");
	while (1)
	{
		scanf("%d", pot);
		if (*pot % 10 == 0 || *pot >= 10)
		{
			if (*pot <= *cash)
			{
				*cash = *cash - *pot;
				return;
			}
			else
			{
				printf("not enough cash, you have %d, try again\n", *cash);
			}
		}
		else
			printf("Error, invalid input, enter a positive multiple of 10\n");
	}
}

/*  print all cards but the last one for the dealer
ignores the last one if desired*/
int print_hand(struct deck* hand, char len, char last)
{
	for (int i = 0; i < len - last; i++) //len starts at 1, change it to start at 0
	{
		print_card(hand, i);
	}
	if (last)
		printf(" ????????");
	printf("\n");

	return;
}

int print_player(struct deck *dealer, struct deck *player, char dealer_len, char player_len)
{
	printf("Dealer: ");
	print_hand(dealer, dealer_len, IGNORE_LAST);
	printf("Player: ");
	print_hand(player, player_len, ALLOW_LAST);

	return;
}

int print_dealer(struct deck* dealer, struct deck* player, char dealer_len, char player_len)
{
	printf("Dealer: ");
	print_hand(dealer, dealer_len, ALLOW_LAST);
	printf("Player: ");
	print_hand(player, player_len, ALLOW_LAST);
	printf("\n");

	return;
}

//handles the player's turn
int player_round(struct deck** player_hand, struct deck* dealer_hand, struct deck** deck_hand, char* player_len, char dealer_len, int* deck_len, int* cash,int* pot)
{
	int score;
	char play = 1, invalid = 1, user_input;
	while (1)
	{
		invalid = 1;
		print_player(dealer_hand, *player_hand, dealer_len, *player_len);
		score = check_score(player_hand);
		//check for black jack or bust
		if (score > 21)
		{
			printf("Bust!\n");
			*pot = 0;
			return 0;
		}
		else if (score == 21)
		{
			printf("Black Jack!\n");
			*cash = *cash + *pot * 2.5;
			return 0;
		}
		else //ask the player if he wants to draw cards or stop
		{
			printf("\nHit or Stand? (type H or S) ");
			while (invalid)
			{
				scanf("%c", &user_input);
				if (user_input == 'h' || user_input == 'H')
				{
					draw_cards(deck_hand, player_hand, deck_len, player_len, 1);
					invalid = 0;
				}
				else if (user_input == 's' || user_input == 'S')
					return score;
				else
					printf("\nInvalid input try again. (H or S) ");
			}
		}
	}
}

int dealer_round(struct deck* player_hand, struct deck** dealer_hand, struct deck** deck_hand, char player_len, char* dealer_len, int* deck_len, int* cash, int* pot, int player_score)
{
	int score;
	char play = 1, invalid = 1, user_input;
	while (1)
	{
		invalid;
		print_dealer(*dealer_hand, player_hand, *dealer_len, player_len);
		score = check_score(dealer_hand);
		//check for black jack or bust
		if (score > 21)
		{
			printf("Dealer Bust!\n");
			*cash = *cash + *pot * 2;
			*pot = 0;
			return;
		}
		else if (score == 21)
		{
			printf("Dealer Black Jack!\n");
			*pot = 0;
			return;
		}
		else if (score > 17)
		{
			if (score < player_score)
			{
				printf("You Win!\n");
				*cash = *cash + *pot * 2;
				*pot = 0;
				return;
			}
			else if (score == player_score) {
				printf("A draw!\n");
				*cash = *cash + *pot;
				*pot = 0;
				return;
			}
			else
			{
				printf("You Loose!\n");
				*pot = 0;
				return;
			}
		}
		else
			draw_cards(deck_hand, dealer_hand, deck_len, dealer_len, 1);
	}
}