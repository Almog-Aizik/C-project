//variables

struct deck {
	unsigned char card;
	int* next;
}deck;

int init_deck(struct deck* head);
int print_deck(struct deck* head); 
int free_deck(struct deck* head);

//due to running only once, initizilation would be done in simplistic way over optimized way for readability

//creates a full deck
int init_deck(struct deck* head)
{
	//variables
	struct deck* current = head;
	int data = 0;
	int suit = 0;

	for (char i = 1; i < 14; i++)
	{
		for (char j = 0; j < 4; j++)
		{
			//get and format data
			data = i << 4;
			suit = 1 << j;
			data = data + suit;
			current->card = data;
			//create the next card and move to it till the end
			if (i == 13 && j == 3);
			else
			{
				current->next = malloc(sizeof(struct deck));
				current = current->next;
			}
		}
		current->next = NULL;
	}
}

//print cards in binary
int print_deck(struct deck* head)
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