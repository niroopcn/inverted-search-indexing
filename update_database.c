#include "main.h"

int updatedb_flag;

Status update_database(char *filename)
{
    if(strstr(filename, ".txt") == NULL)
    {
        char choice;
        printf("\"%s\" is not a .txt file\nAre you sure you want to backup from this file? (Y/y): ", filename);
        scanf("%c", &choice);
        while(getchar() != '\n');

        if(!(choice == 'Y' || choice == 'y'))
        return e_error;
    }
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("fopen");
        return e_error;
    }

    fseek(fptr, 0, SEEK_END);
    if(ftell(fptr) == 0)
    {
	printf("File is Empty, cannot restore backup.\n");
	return e_error;
    }
    fseek(fptr, 0, SEEK_SET);
    
    int error_check;
    while (feof(fptr) == e_success)
    {
        if (fgetc(fptr) != '#')
            return e_failure;

        int index;
        if((error_check = fscanf(fptr, "%d;\n", &index)) == EOF || error_check == 0)
        return e_failure;
        index = index % 27; //safety cond. if non backup files are passed like main.c

        char word_buffer[20];
        if((error_check = fscanf(fptr, "%19[^;];", word_buffer)) == EOF || error_check == 0) 
        return e_failure;

        int file_count;
        if((error_check = fscanf(fptr, "%d;", &file_count)) == EOF || error_check == 0) 
        return e_failure;

        for (int i = 0; i < file_count; i++)
        {
            char file_buffer[20];
            if((error_check = fscanf(fptr, "%19[^;];", file_buffer)) == EOF || error_check == 0) 
            return e_failure;

            int word_count;
            if((error_check = fscanf(fptr, "%d;", &word_count)) == EOF || error_check == 0)
            return e_failure;

            //update flags only when appending
            updatedb_flag = 1;
            createdb_flag = 1;

            //append data to Database (HashTable/MainNode)
            append_to_database(index, word_count, file_buffer, file_count, word_buffer, e_updatedb);
        }
        
        //remove '#' and '\n'
        char buf[2];
        fscanf(fptr, "%2[^\n]\n", buf);    
    }
    return e_success;
}
