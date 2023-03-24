#include "main.h"

int createdb_flag;

Status create_database()
{
    if(updatedb_flag)
    {
        printf("------------------------------------------------------\nDatabase cannot be created after updating using backup\nPlease exit the program and re-run\n------------------------------------------------------\n");
        return e_error;
    }
    
    if(createdb_flag)
    {
        printf("--------------------------------------------------------------------------------------\nDatabase already created!\nPlease exit the program and re-run or use \"Update Database\" to load from a backup file\n--------------------------------------------------------------------------------------\n");
        return e_error;
    }
    
    createdb_flag = 1;

    if (get_words_from_files() == e_failure)
        return e_failure;

    return e_success;
}

Status get_words_from_files()
{
    FileList *temp = head;
    while (temp != NULL)
    {
        FILE *fptr = fopen(temp->filename, "r");
        if (fptr == NULL)
        {
            perror("fopen");
            return e_failure;
        }

        while (feof(fptr) == e_success)
        {
            char buffer[20] = {0};
            int ret = fscanf(fptr, "%19s", buffer);

            // printf("ret is %d, buffer is %s\n", ret, buffer);

            // finding index for hashing
            int index = find_index(buffer);

            // store in hash_table
            if (ret == 1)
                append_to_database(index, 1, temp->filename, 1, buffer, e_createdb);
        }
        fclose(fptr);
        temp = temp->next;
    }
}
