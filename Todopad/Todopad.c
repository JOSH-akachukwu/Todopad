/*
This program creates a Cli interface for writing Todos {tasks} and then stores them in a file for later use.
for efficiency it caches the todos stored in file to memory.

Aurthor -> Onwuemenyi Joshua .A
*/
#include "./tp_headers/tp_core_utils.h"

int main(void)
{
    char *file_name = "todolist.txt";
    FILE *TD = fopen(file_name, "a+");
    if (!TD)
    {
        printf("Error handling file");
        return EXIT_FAILURE;
    }
    Cache userdo = {
        .capacity = 2,
        .todos = malloc(sizeof(char *) * 2),
        .current_count = 0,
    };
    char buff[300]; // to accommodate very long todos.
    int cont = 1;
    int index;
    int not_first = 0;
    if (!is_file_empty(TD))
    {
        cache_file(TD, &userdo);
        print_cache(&userdo);
    };
    fclose(TD);

    while (cont)
    {
        printf("\n\nOptions :\n~ (1) to add a Todo\n~ (2) to remove todo.\n~ (3) to save and exit, (4) to exit without saving.\n~ (5) to edit todo.\n->> ");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = 0;
        int option = atoi(buff);
        switch (option)
        {
        case 1:
            printf("Enter Todo ->> ");
            fgets(buff, sizeof buff, stdin);
            add_todo(&userdo, buff);
            break;
        case 2:
            printf("Enter index of Todo : ");
            fgets(buff, sizeof buff, stdin);
            buff[strcspn(buff, "\n")] = 0;
            if ((index = atoi(buff)) == 0)
            {
                printf("\"%s\" ~ is not a valid index", buff);
            }
            else
            {
                remove_todo(&userdo, index);
                print_cache(&userdo);
            };
            break;
        case 3:
            if (not_first)
                save_cache(file_name, &userdo);
            cont = 0;
            break;
        case 4:
            cont = 0;
            break;
        case 5:
            printf("Enter index of todo : ");
            fgets(buff, sizeof buff, stdin);
            buff[strcspn(buff, "\n")] = 0;
            if ((index = atoi(buff)) == 0 || index > userdo.current_count)
            {
                printf("\"%s\" ~ is not a valid index", buff);
            }
            else
            {
                printf("Enter new todo : ");
                fgets(buff, sizeof buff, stdin);
                (edit_todo(&userdo, buff, index)) ? printf("Done") : printf("Error!");
                print_cache(&userdo);
            }
            break;
        default:
            printf("\"%s\" is not a Valid option.", buff);
            break;
        }
        not_first = 1;
    }
    free_cache(&userdo);
}

