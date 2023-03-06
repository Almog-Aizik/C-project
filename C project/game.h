#include <stdio.h>

#define IGNORE_LAST 1
#define ALLOW_LAST 0


int can_play(int cash);
int betting(int cash, int pot);
int print_hand(struct deck *hand, char len, char status);
int print_player(struct deck* dealer, struct deck* player, char dealer_len, char player_len);

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
	for (int i = 1; i < len - last; i++)
	{
		print_card(hand, i);
	}
	if (last)
		printf("????????");
	printf("\n");
}

int print_player(struct deck *dealer, struct deck *player, char dealer_len, char player_len)
{
	printf("Dealer: ");
	print_hand(dealer, dealer_len + 1, IGNORE_LAST);
	printf("Player: ");
	print_hand(player, player_len + 1, ALLOW_LAST);
}