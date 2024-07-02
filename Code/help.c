#include <stdio.h>
#include "help.h"
#include "main.h" // Add the inclusion of the main.h header

extern char *builtin_commands[]; // Declare the array of built-in commands from main.c

int num_builtins(); // Declare the function prototype for num_builtins() from main.c

int show_help(char **args) {
  int i;

  printf("The following are built-in:\n");

  for (i = 0; i < num_builtins(); i++) {
    printf("  %s\n", builtin_commands[i]);
  }

  return 1;
}
