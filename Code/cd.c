#include <stdio.h>
#include <unistd.h>
#include "cd.h"
#include "main.h"

int change_directory(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "shell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("shell");
    }
  }
  return 1;
}
