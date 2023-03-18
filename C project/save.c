#include "save.h"

/* asks the user to load a save
 loads the amount of money a user has if the user says yes and it exists
 otherwise returns 1000 */
int load_save()
{
	FILE* save;
	int data;
	char user_input;
	printf("Do you want to load the save? (Y/N) ");
	while (1)
	{
		scanf(" %c", &user_input);
		if (user_input == 'Y' || user_input == 'y')
		{
			save = fopen("save.txt", "r");
			if (save != NULL)
			{
				rewind(save); // just to be safe
				fscanf(save, "%d", &data);
				fclose(save);
				return data;
			}
			return 1000;
		}
		else if (user_input == 'N' || user_input == 'n')
			return 1000;
		else
			printf("Invalid input, enter Y/N: ");
	}
}

//saves the data to file
int save_to_file(int data)
{
	FILE* save;
	char user_input;
	printf("Do you want to save the game? (Y/N) ");
	while (1)
	{
		scanf(" %c", &user_input);
		if (user_input == 'Y' || user_input == 'y')
		{
			save = fopen("save.txt", "w");
			rewind(save); // just to be safe
			fprintf(save, "%d", data);
			fclose(save);
			return 0;
		}
		else if (user_input == 'N' || user_input == 'n')
			return 1;
		else
			printf("Invalid input, enter Y/N: ");
	}
}