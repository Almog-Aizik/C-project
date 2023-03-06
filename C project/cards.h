#include <stdio.h>

#define SUIT_MASK 0x0F
#define VALUE_MASK 0xF0

struct deck {
	unsigned char card;
	struct deck* next;
};

int init_deck(struct deck* head, char *len);
int print_deck(struct deck* head); 
int free_deck(struct deck* head);
int draw_card(struct deck** deck, struct deck** hand, char* deck_len, char times);
int print_card(struct deck* hand, char card);

//creates a full deck
int init_deck(struct deck* head, int *len)
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
				current->next = malloc(sizeof(struct deck));
				current = current->next;
			}
			count++;
		}
	}
	current->next = NULL;
	*len = count;
}

/*print cards in binary
* testing only, delete before sending */
int print_deck_binary(struct deck* head)
{
	unsigned char data;
	struct deck* current = head;
	while (current != NULL)
	{
		data = current->card;
		while (data)
		{
			printf("%d", (data & 1)); //print 1 bit at a time 
			data = data >> 1; //move to the next bit
			
		}
		printf("\n");
		current = current->next;
	}
}

//free the memory of the deck
int free_deck(struct deck* head)
{
	struct deck* current = head;
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
int draw_cards(struct deck **deck, struct deck **hand, int *deck_len, int *hand_len, int times)
{
	//get variables to allow walking on the chained list
	char rand_num;
	struct deck* previous = *deck, *current = *deck, *hand_last = *hand;
	struct deck* next = current->next;
	for (char i = 0; i < times; i++)
	{
		//pull a random card and detach it from the deck
		rand_num = rand() % *deck_len;
		for (char j = 0; j < rand_num; j++)
		{
			if (current->next != NULL)
			{
				previous = current;
				current = current->next;
				next = current->next;
			}
		}
		previous->next = next;
		current->next = NULL;
		*deck_len = *deck_len - 1;
		//add the card to the hand
		if (*hand == NULL)
		{
			*hand = current;
		}
		else
		{
			hand_last = *hand;
			while (hand_last->next != NULL)
				hand_last = hand_last->next;
			hand_last->next = current;
		}
		*hand_len = *hand_len + 1;
	}
}

int print_card(struct deck* **hand, char card)
{
	char suit, value;
	struct deck* position = hand;
	for (char i = 0; i < card; i++)
	{
		if (position->next != NULL)
			position = position->next;
		else
			return;
		// extract the data from the card
		suit = position->card && SUIT_MASK;
		value = position->card && VALUE_MASK;
		value = value >> 4;
		/*--------------------------------*/
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
			printf("Hearts, ");
			break;
		case 2: //0010
			printf("Diamonds, ");
			break;
		case 4: //0100
			printf("Spades, ");
			break;
		case 8: //1000
			printf("Clubs, ");
			break;
		}
	}
}