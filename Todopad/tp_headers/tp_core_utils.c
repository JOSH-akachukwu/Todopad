#include "tp_core_utils.h"

int is_file_empty(FILE *Fp)
{
    int c = fgetc(Fp);
    if (c < 0)
    {
        printf("Fresh start..");
        return 1;
    }

    BTT(Fp);
    return 0;
}

void read_file(FILE *Fp)
{
    char buff[100];
    int count = 1;
    printf("\t\t~Existing Todos~\n");
    while ((fgets(buff, sizeof buff, Fp)))
    {
        printf("%d) %s", count, buff);
        count++;
    }
    BTT(Fp);
}

void add_todo(struct TODO *cache, char *buff)
{
    scale_cache(cache);
    if (strlen(buff) > 1)
    {
        cache->todos[cache->current_count] = strdup(buff);
        cache->current_count++;
        print_cache(cache);
    }
    else
    {
        printf("Can't add empty Todo");
    }
}

void scale_cache(struct TODO *cache)
{
    if (cache->current_count >= cache->capacity)
    {
        cache->capacity *= 2;
        char **more_mem = realloc(cache->todos, sizeof(char *) * cache->capacity);
        if (!more_mem)
        {
            printf("Memory error!. Exiting");
            exit(1);
        }
        cache->todos = more_mem;
    }
}

void cache_file(FILE *Fp, struct TODO *cache)
{
    char buff[300]; // just to accommodate for very long todos.
    while ((fgets(buff, sizeof buff, Fp)) != NULL)
    {
        scale_cache(cache);
        cache->todos[cache->current_count] = strdup(buff);
        cache->current_count += 1;
    }
    // print_cache(cache);
    printf("\nTodos Cached into memeory!");
    BTT(Fp);
}

void free_cache(struct TODO *cache)
{
    for (int i = 0; i < cache->current_count; i++)
    {
        free(cache->todos[i]);
    }
    free(cache->todos);
    cache->todos = NULL;
    printf("Cache freed!");
}

char *remove_todo(struct TODO *cache, int index)
{
    int valid = 0;
    char removed[300];
    for (int i = 0; i < cache->current_count; i++)
    {
        if (i + 1 == index)
        {
            strcpy(removed, cache->todos[i]);
            free(cache->todos[i]);
            valid = 1;
        }
    }
    if (valid)
    {
        cache->current_count--;
        for (int i = 0; i <= cache->current_count; i++)
        {
            if ((i + 1 >= index))
            {
                if (i == cache->current_count)
                    break;
                cache->todos[i] = cache->todos[i + 1];
            }
        }
        printf("Removed ~ %s ", removed);
        return "Done.";
    }
    else
        return "No such todo!";
}

void print_cache(struct TODO *cache)
{
    int count = 1;
    printf("\n");
    for (int i = 0; i < cache->current_count; i++)
    {
        printf("%d) %s", count, cache->todos[i]);
        count++;
    }
}

void save_cache(const char *name_of_file, struct TODO *cache)
{
    FILE *TD = fopen(name_of_file, "w");
    for (int i = 0; i < cache->current_count; i++)
    {
        fprintf(TD, "%s", cache->todos[i]);
    }
    printf("Todos saved.");
    fclose(TD);
}

int edit_todo(struct TODO *cache, char *buff, int index)
{
    int valid = 0;
    for (int i = 0; i < cache->current_count; i++)
    {
        if (i + 1 == index)
        {
            free(cache->todos[i]);
            cache->todos[i] = strdup(buff);
            valid = 1;
        }
    }
    if (valid)
        return 1;
    else
        return 0;
}

// void remove_all(struct TODO *cache)
// {
//     // Hopefully I'll implement this later or when I add graphics.
// }