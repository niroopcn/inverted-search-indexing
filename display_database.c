#include "main.h"

Status display_database()
{
    if(createdb_flag == 0)
        return e_failure;
    
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < 27; i++)
    {
        if(words[i].link == NULL) continue;
        if(!i)
            printf("[Index] [Word(s)]\t[File Count]\t   [File Name]\t   [Word Count]\n");

        MainNode *temp = words[i].link;
        while (temp != NULL)
        {
            printf("[%d]\t[%s]\t\t[%d] file(s)\t", i, temp->word, temp->file_count);
            SubNode *sub_temp = temp->sub_link;
            int p = 'a';
            while (sub_temp != NULL)
            {
                printf("%c. [%s] ---> [%d] time(s)\t\t", p++, sub_temp->filename, sub_temp->word_count);
                sub_temp = sub_temp->sub_link;
            }
            printf("\n");
            temp = temp->main_link;
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");

    return e_success;

}