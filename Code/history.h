#ifndef HISTORY_H
#define HISTORY_H

#define MAX_HISTORY_SIZE 100

void initialize_history();
void add_to_history(char **args);
int print_history(char **args);

#endif
