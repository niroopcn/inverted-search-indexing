#ifndef _MAIN_H
#define _MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum
{
    e_success,
    e_failure,
    e_error
} Status;

typedef enum
{
    e_createdb,
    e_updatedb
} Mode;
 
typedef struct sub_node
{
    int word_count;
    char filename[20];
    struct sub_node* sub_link;
} SubNode;

typedef struct main_node
{
    int file_count;
    char word[20];
    SubNode* sub_link;
    struct main_node* main_link;
} MainNode;

typedef struct
{
    MainNode* link;
} HashTable;

typedef struct file_list
{
    char filename[20];
    struct file_list* next;
} FileList;

extern HashTable words[27];
extern FileList *head;
extern int createdb_flag;
extern int updatedb_flag;

Status read_and_validate(int argc, char *argv[]);
Status check_file(char *filename);
void insert_filename_to_filelist(char *buffer);

Status create_database();
int find_index(char* buffer);
Status get_words_from_files();
void append_to_database(int index, int word_count, char *file_temp, int file_count, char *buffer, Mode mode);

Status display_database();

Status search_database(char *buffer);

Status save_database();

Status update_database(char* filename);

void free_memory();

void *malloc_custom(long unsigned int size);
extern long unsigned int total_bytes_allocated;

void free_custom(void *address, long unsigned int size);
extern long unsigned int total_bytes_freed;

#endif