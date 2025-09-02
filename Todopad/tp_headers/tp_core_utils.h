#ifndef TP_HEADER
#define TP_HEADER

#ifndef IO
#define IO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

// BACK TO TOP
#define BTT(Fp)     \
    do              \
    {               \
        fflush(Fp); \
        rewind(Fp); \
    } while (0)

typedef struct TODO
{
    int capacity;
    char **todos;
    int current_count;
} Cache;

void print_cache(struct TODO *cache);
int is_file_empty(FILE *Fp);
void read_file(FILE *Fp);
void cache_file(FILE *Fp, struct TODO *cache);
void scale_cache(struct TODO *cache);
void add_todo(struct TODO *cache, char *buff);
char *remove_todo(struct TODO *cache, int index);
void free_cache(struct TODO *cache);
void save_cache(const char *name_of_file, struct TODO *cache);
int edit_todo(struct TODO *cache, char *buff, int index);
// void remove_all(struct TODO *cache);

#endif