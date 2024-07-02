#include <stdio.h>
#include <string.h>
#include "history.h"

static char history[MAX_HISTORY_SIZE][1024];
static int history_count = 0;
static int current_index = 0;

void initialize_history() {
    memset(history, 0, sizeof(history));
    history_count = 0;
    current_index = 0;
}

// void add_to_history(const char* command) {
//     if (strlen(command) == 0) {
//         return;
//     }

//     strncpy(history[current_index], command, sizeof(history[current_index]) - 1);
//     current_index = (current_index + 1) % MAX_HISTORY_SIZE;

//     if (history_count < MAX_HISTORY_SIZE) {
//         history_count++;
//     }
// }

void add_to_history(char **args) {
    int i;
    char input_line[1024] = "";
    
    for (i = 0; args[i] != NULL; i++) {
        strcat(input_line, args[i]);
        strcat(input_line, " ");
    }

    if (strlen(input_line) == 0) {
        return;
    }

    strncpy(history[current_index], input_line, sizeof(history[current_index]) - 1);
    current_index = (current_index + 1) % MAX_HISTORY_SIZE;

    if (history_count < MAX_HISTORY_SIZE) {
        history_count++;
    }
}


int print_history(char **args) {
    int i, index;

    if (history_count == 0) {
        printf("No command history\n");
        return 0;
    }

    printf("Command History:\n");

    index = (current_index - history_count + MAX_HISTORY_SIZE) % MAX_HISTORY_SIZE;
    for (i = 0; i < history_count; i++) {
        printf("%d. %s\n", i + 1, history[index]);
        index = (index + 1) % MAX_HISTORY_SIZE;
    }
    return 1;
}

