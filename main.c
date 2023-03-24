#include "main.h"

HashTable words[27];
FileList *head = NULL;

int main(int argc, char *argv[])
{
	if (argc < 2)
		return fprintf(stderr, "[ERROR] Please provide atleast 1 file in CLA\nUSAGE: ./a.out file1.txt file2.txt...\n");

	//register function to free dynamic memory while exiting program
	atexit(free_memory);

	// validate CLA files and store names in FileList linked list
	if (read_and_validate(argc, argv) == e_failure)
		return e_failure;
	
	// make links NULL in HashTable
	for (int i = 0; i < 27; i++)
		words[i].link = NULL;

	int choice;
	char exit_flag = 'y';

	while (exit_flag == 'Y' || exit_flag == 'y')
	{
		printf("Menu:\n1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\nEnter Choice: ");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
		{
			int ret;
			if ((ret = create_database()) == e_failure)
				return e_failure;
			else if(ret == e_success)
				printf("------------------------------\nDatabase created Successfully!\n------------------------------\n");
		}
		break;

		case 2:
			if(display_database() == e_failure)
			printf("--------------------------------------------------------------------------------------------------\nDatabase does not exist!\nPlease choose either option 1 or 5 to create a database or update using backup file and then retry\n--------------------------------------------------------------------------------------------------\n");
			break;

		case 3:
		{
			char search_word[20];
			printf("Enter word to search: ");
			scanf("%s", search_word);
			while (getchar() != '\n');

			if (search_database(search_word) == e_failure)
				printf("--------------------------------------------\nWord \"%s\" not found\n--------------------------------------------\n", search_word);
		}
		break;

		case 4:
		{
			int ret;
			if((ret = save_database()) == e_failure)
			printf("--------------------------------------------------------\nDatabase is not created to be saved as backup!\nPlease run \"Create Database\" using Option 1 and then save.\n--------------------------------------------------------\n");
			else if(ret == e_success)
			printf("----------------------------\nDatabase Saved Successfully!\n----------------------------\n");
		}
		break;

		case 5:
		{
			char update_file[20] = {0};
			printf("Enter name of backup file(.txt) to update: ");
			scanf("%s", update_file);
			while (getchar() != '\n');

			int ret;
			if((ret = update_database(update_file)) == e_success)
			printf("------------------------------\nDatabase Updated Successfully!\n------------------------------\n");
			else if(ret == e_failure)
			fprintf(stderr, "[ERROR] %s file is corrupted, data might be partially restored, please check \"Display Database\"\n", update_file);
		}
			break;

		case 6:
			return e_success;

		default:
			fprintf(stderr, "Enter correct choice\n");
		}

		printf("Do you want to continue? (Y/y): ");
		scanf("%c", &exit_flag);
		while (getchar() != '\n')
			;
	}
	return e_success;
}

int find_index(char *buffer)
{
	if (buffer[0] >= 'a' && buffer[0] <= 'z')
		return buffer[0] % 97;
	else if (buffer[0] >= 'A' && buffer[0] <= 'Z')
		return buffer[0] % 65;
	else
		return 26;
}
