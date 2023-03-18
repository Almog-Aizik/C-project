#include "cards.h"

//creates a full deck
void init_deck(struct deck* head, char* len)
{
	//variables
	struct deck* current = head;
	char data = 0;
	char suit = 0;
	char count = 0;
	for (char i = 1; i < 14; i++)
	{
		for (char j = 0; j < 4; j++)
		{
			//get and format data
			data = i << 4;
			suit = 1 << j;
			data = data + suit;
			current->card = data;
			//create the next card and move to it till the last card
			if (i == 13 && j == 3);
			else
			{
				current->next = (struct deck*)malloc(sizeof(struct deck));
				current = current->next;
			}
			count++;
		}
	}
	current->next = NULL;
	//test there are 52 cards in deck
	*len = count;
}

//free the memory of the deck
void free_deck(struct deck** head)
{
	struct deck* current = *head;
	struct deck* next = current->next;
	while (current != NULL)
	{
		current->next = NULL;
		free(current);
		if (next->next != NULL)
		{
			current = next;
			next = next->next;
		}
		else
			current = NULL;

	}
}

//draw cards x amount of random cards from deck to hand
void draw_cards(struct deck** deck, struct deck** hand, char* deck_len, char* hand_len, int times)
{
	//get variables to allow walking on the chained list
	unsigned int rand_num;
	struct deck* previous, * current, * hand_last;
	for (char i = 0; i < times; i++)
	{
		previous = *deck;
		current = *deck;
		//pull a random card and detach it from the deck
		rand_num = rand() % *deck_len;
		if (rand_num > 0)
		{
			for (int j = 0; j < rand_num; j++)
			{
				if (current->next != NULL) // special case that should never happen
				{
					previous = current;
					current = current->next;
				}
			}
			previous->next = current->next;
		}
		else //1st card special case
			*deck = current->next;
		*deck_len = *deck_len - 1;

		//add the card to the hand
		if (*hand == NULL)
		{
			*hand = current;
			(*hand)->next = NULL;
		}
		else
		{
			hand_last = *hand;
			while (hand_last->next != NULL)
				hand_last = hand_last->next;
			hand_last->next = current;
			current->next = NULL;
		}
		*hand_len = *hand_len + 1;
	}
}

//prints all the cards in an hand
void print_card(struct deck* hand, char card)
{
	unsigned char suit, value;
	struct deck* position = hand;
	for (char i = 0; i < card; i++)
	{
		if (position->next != NULL)
			position = position->next;
		else
			return;
	}
	// extract the data from the card
	suit = position->card & SUIT_MASK;
	value = position->card & VALUE_MASK;
	value = value >> 4;
	/*--------------------------------*/
	if (card) // cosmetic spacing
		printf(", ");
	if (value <= 10 && value > 1)
		printf("%d of ", value);
	else
	{
		switch (value)
		{
		case 1:
			printf("Ace of ");
			break;
		case 11:
			printf("Jack of ");
			break;
		case 12:
			printf("Queen of ");
			break;
		case 13:
			printf("King of ");
			break;
		}
	}
	switch (suit)
	{
	case 1:  //0001
		printf("Hearts");
		break;
	case 2: //0010
		printf("Diamonds");
		break;
	case 4: //0100
		printf("Spades");
		break;
	case 8: //1000
		printf("Clubs");
		break;
	}
}

//moves all cards from one hand to another
void move_all_cards(struct deck** hand, struct deck** target)
{
	struct deck* last = *target;
	while (last->next != NULL)
	{
		//printf("%d\n", last);
		last = last->next;
	}
	last->next = *hand;
	*hand = NULL;
}

//returns all cards to the hand
void return_to_deck(struct deck** player, struct deck** dealer, struct deck** deck, char* player_len, char* dealer_len, char* deck_len)
{
	move_all_cards(player, deck);
	move_all_cards(dealer, deck);
	//reset the lens to their proper values
	*player_len = 0;
	*dealer_len = 0;
	*deck_len = 52;
}

//gets the value of an hand
int check_score(struct deck** hand)
{
	struct deck* current = *hand;
	int sum = 0, value, ace = 0;
	while (current != NULL)
	{
		value = current->card & VALUE_MASK;
		value = value >> 4;
		if (value == 1)
			ace = 1;
		else if (value > 10)
			value = 10;
		sum = sum + value;
		current = current->next;
	}
	if (ace && sum <= 11)
		sum = sum + 10;
	return sum;
}