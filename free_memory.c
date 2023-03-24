#include "main.h"

void free_memory(void)
{
    //freeing HashTable
    for(int i = 0; i < 27; i++)
    {
	if(words[i].link == NULL) continue;

	MainNode *temp = words[i].link;
	while (temp != NULL)
	{
	    if(temp->sub_link != NULL)
	    {
		SubNode *sub_temp = temp->sub_link;
		while (sub_temp != NULL)
		{
		    temp->sub_link = sub_temp->sub_link;
		    free_custom(sub_temp, sizeof(SubNode));
		    sub_temp = temp->sub_link;
		}
	    }
	    words[i].link = temp->main_link;
	    free_custom(temp, sizeof(MainNode));
	    temp = words[i].link;
	}
    }

    //freeing FileList linked list
    FileList *temp = head;
    while(head != NULL)
    {
	head = temp->next;
	free_custom(temp, sizeof(FileList));
	temp = head;
    }
    if(createdb_flag)
    {
	printf("--------------------------------------------------------------\nMemory Management:\n");
	printf("%ld bytes allocated in total & %ld bytes freed in total\n", total_bytes_allocated, total_bytes_freed);

	if(total_bytes_allocated == total_bytes_freed)
	    printf("All heap blocks were freed, ");
	else
	    printf("Partial Memory freed, %ld bytes lost, ", total_bytes_allocated - total_bytes_freed);

	printf("Exiting program...\n--------------------------------------------------------------\n");
    }
}

long unsigned int total_bytes_allocated;
long unsigned int total_bytes_freed;

void* malloc_custom(long unsigned int size)
{
    void *ptr;
    if((ptr = malloc(size)) != NULL)
	total_bytes_allocated += size;
    return ptr;
}

void free_custom(void *address, long unsigned int size)
{
    free(address);
    total_bytes_freed += size;
}
