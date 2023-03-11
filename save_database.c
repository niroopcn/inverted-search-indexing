#include "main.h"

Status save_database()
{
    if (createdb_flag == 0)
        return e_failure;

    char filename[20] = {0};
    printf("Enter name of backup file(.txt): ");
    scanf("%s", filename);
    while (getchar() != '\n');

    char *ptr;
    if ((ptr = strstr(filename, ".txt")) == NULL)
    {
        if ((ptr = strstr(filename, ".")) != NULL)
            *ptr = '\0';

        printf("Filename extension doesn't match .txt, concatenating %s with .txt\n", filename);
        strcat(filename, ".txt");
        printf("Final Backup filename is %s\n", filename);
    }

    FILE *fptr = fopen(filename, "w");
    if(fptr == NULL)
    {
        perror("fopen");
        return e_error;
    }

    for (int i = 0; i < 27; i++)
    {
        if (words[i].link == NULL)
            continue;

        MainNode *temp = words[i].link;

        while (temp != NULL)
        {
            // update index
            fprintf(fptr, "#%d;\n", i);

            // update word
            fprintf(fptr, "%s;", temp->word);

            // update filecount
            fprintf(fptr, "%d;", temp->file_count);

            // update files
            SubNode *sub_temp = temp->sub_link;
            while (sub_temp != NULL)
            {
                // update sub node data
                fprintf(fptr, "%s;", sub_temp->filename);
                fprintf(fptr, "%d;", sub_temp->word_count);
                sub_temp = sub_temp->sub_link;
            }

            fputc('#', fptr);
            fputc('\n', fptr);

            temp = temp->main_link;
        }
    }

    fclose(fptr);
    return e_success;
}
