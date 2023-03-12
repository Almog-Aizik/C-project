#include <stdlib.h>

int load_save();
int save_to_file(int data);


/* asks the user to load a save
 loads a save if the user says yes and it exists
 otherwise returns 1000 */
int load_save()
{
	FILE *save;
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
				rewind(save);
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
			rewind(save);
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