#include "main.h"

void append_to_database(int index, int word_count, char *file_temp, int file_count, char *buffer, Mode mode)
{   
    MainNode *temp = words[index].link, *prev = temp;
    while (temp != NULL)
    {
        if (strcmp(temp->word, buffer) == e_success)
        {
            SubNode *sub_temp = temp->sub_link, *sub_prev = sub_temp;
            while (sub_temp != NULL)
            {
                if (strcmp(sub_temp->filename, file_temp) == e_success)
                {
                    if(mode == e_createdb)
                    sub_temp->word_count++;

                    return;
                }
                sub_prev = sub_temp;
                sub_temp = sub_temp->sub_link;
            }
            // when new file is found
            if (sub_temp == NULL)
            {
                SubNode *sub = malloc_custom(sizeof(SubNode));
                sub->word_count = word_count;
                strcpy(sub->filename, file_temp);
                sub->sub_link = NULL;

                // link new sub node
                sub_prev->sub_link = sub;

                // increment file count
                if(mode == e_createdb)
                temp->file_count++;
                return;
            }
        }
        prev = temp;
        temp = temp->main_link;
    }

    // if appending new main node
    if (temp == NULL)
    {
        MainNode *main = malloc_custom(sizeof(MainNode));
        main->file_count = file_count;
        strcpy(main->word, buffer);
        main->main_link = NULL;

        SubNode *sub = malloc_custom(sizeof(SubNode));
        sub->word_count = word_count;
        strcpy(sub->filename, file_temp);
        sub->sub_link = NULL;

        main->sub_link = sub;

        if (words[index].link == NULL)
            words[index].link = main;
        else
            prev->main_link = main;
    }
}