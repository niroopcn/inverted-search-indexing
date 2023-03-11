#include "main.h"

Status search_database(char *buffer)
{
    int index = find_index(buffer);

    if(words[index].link == NULL) return e_failure;
    else
    {
        MainNode *temp = words[index].link;
        while (temp != NULL)
        {
            if(strcmp(temp->word, buffer) == e_success)
            {
                printf("--------------------------------------------\n");
                printf("Word \"%s\" is present in %d file(s)\n", buffer, temp->file_count);
                SubNode *sub_temp = temp->sub_link;
                while(sub_temp != NULL)
                {
                    printf("In file: %s - %d time(s)\n", sub_temp->filename, sub_temp->word_count);
                    sub_temp = sub_temp->sub_link;
                }
                printf("--------------------------------------------\n");
                return e_success;
            }
            temp = temp->main_link;
        }
    }
    return e_failure;
}