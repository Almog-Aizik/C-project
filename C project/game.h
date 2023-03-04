#include <stdlib.h>

int load_save(FILE *save);


/* asks the user to load a save
 loads a save if the user says yes and it exists
 otherwise returns 1000 */
int load_save(FILE *save)
{
	while (1)
	{
		char user_input[2];
		printf("Do you want to load the save? (Y/N) ");
		scanf("%s", user_input);
		fflush(stdin);
		if (user_input == "Y" || user_input == "y")
		{
			save = fopen("save.txt", "r+");
			return 1000;
		}
		else if (user_input == "N" || user_input == "n")
			return 1000;
		else
			printf("Invalid input, enter Y/N: ");
	}
}