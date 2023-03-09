#include <stdlib.h>

int load_save();


/* asks the user to load a save
 loads a save if the user says yes and it exists
 otherwise returns 1000 */
int load_save()
{
	FILE *save;
	int data;
	printf("Do you want to load the save? (Y/N) ");
	while (1)
	{
		char user_input = { 0 }; // zero out the input to prevent infinite loop
		scanf("%c", &user_input);
		if (user_input == 'Y' || user_input == 'y')
		{
			save = fopen("save.txt", "r");
			if (save != NULL)
			{
				rewind(save);
				data = getw(save);
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