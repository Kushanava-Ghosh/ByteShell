#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alias.h"

#define MAX_ALIASES 100
#define MAX_ALIAS_LENGTH 50
#define MAX_COMMAND_LENGTH 100

struct Alias {
    char alias[MAX_ALIAS_LENGTH];
    char command[MAX_COMMAND_LENGTH];
};

struct Alias alias_table[MAX_ALIASES];
int num_aliases = 0;

void initialize_alias_table() {
    num_aliases = 0;
}

int add_alias(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Usage: alias <alias_name> <command>\n");
        return 1;
    }

    if (num_aliases >= MAX_ALIASES) {
        printf("Alias table is full. Cannot add more aliases.\n");
        return 1;
    }

    strcpy(alias_table[num_aliases].alias, args[1]);
    strcpy(alias_table[num_aliases].command, args[2]);
    num_aliases++;

    return 1;
}

int show_aliases(char **args) {
    if (num_aliases == 0) {
        printf("No aliases found.\n");
        return 1;
    }

    printf("Aliases:\n");
    for (int i = 0; i < num_aliases; i++) {
        printf("%s=%s\n", alias_table[i].alias, alias_table[i].command);
    }

    return 1;
}

int unalias(char **args) {
    if (args[1] == NULL) {
        printf("Usage: unalias <alias_name>\n");
        return 1;
    }

    int alias_found = 0;

    for (int i = 0; i < num_aliases; i++) {
        if (strcmp(alias_table[i].alias, args[1]) == 0) {
            // Shift the remaining aliases to fill the gap
            for (int j = i; j < num_aliases - 1; j++) {
                strcpy(alias_table[j].alias, alias_table[j + 1].alias);
                strcpy(alias_table[j].command, alias_table[j + 1].command);
            }

            num_aliases--;
            alias_found = 1;
            break;
        }
    }

    if (!alias_found) {
        printf("Alias '%s' not found.\n", args[1]);
        return 1;
    }

    return 1;
}
char* replace_alias(char *command) {
    for (int i = 0; i < num_aliases; i++) {
        if (strcmp(command, alias_table[i].alias) == 0) {
            return strdup(alias_table[i].command);
        }
    }
    return NULL;
}

