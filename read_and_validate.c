#include "main.h"

Status read_and_validate(int argc, char *argv[])
{
	int validated;
	for (int i = 1; i < argc; i++)
	{
		validated = 1;
		if (strstr(argv[i], ".txt") == NULL)
		{
			fprintf(stderr, "[ERROR] %s is not a .txt file\n", argv[i]);
			validated = 0;
		}
		else
		if (check_file(argv[i]) == e_failure)
		{
			fprintf(stderr, "[ERROR] %s is empty or does not exist\n", argv[i]);
			validated = 0;
		}

		// Append filenames (argv[i]) to FileList Linked list
		if(validated)
		insert_filename_to_filelist(argv[i]);
	}

	//check if filelist linked list is not empty
	return head != NULL ? e_success : e_failure;
}

Status check_file(char *filename)
{
	FILE *fptr = fopen(filename, "r");
	if (fptr == NULL)
		return e_failure;

	fseek(fptr, 0, SEEK_END);

	int ret = ftell(fptr);
	fclose(fptr);

	// if ftell is at 0th position return failure for file empty
	return ret ? e_success : e_failure;
}

void insert_filename_to_filelist(char *buffer)
{
	FileList *temp = head, *prev = temp;
	while (temp != NULL)
	{
		if (strcmp(temp->filename, buffer) == 0)
		{
			fprintf(stderr, "%s is repeated, ignoring insertion into linked list...\n", buffer);
			break;
		}
		prev = temp;
		temp = temp->next;
	}
	// to confirm if filename was not already present
	// prev stores last node address
	// if temp is NULL, then no repetition
	if (temp == NULL)
	{
		printf("SUCCESSFULLY validated %s\n", buffer);
		FileList *new = malloc_custom(sizeof(FileList));
		strcpy(new->filename, buffer);
		new->next = NULL;

		// if head pointer is NULL, update with new
		if (head == NULL)
			head = new;
		else
			prev->next = new;
	}
}
