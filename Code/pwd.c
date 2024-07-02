#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pwd.h"

#define INITIAL_BUFFER_SIZE 1024

int print_working_directory(char **args) {
  char *cwd = NULL;
  size_t size = INITIAL_BUFFER_SIZE;

  while (1) {
    cwd = realloc(cwd, size);
    if (cwd == NULL) {
      perror("shell");
      return 1;
    }

    if (getcwd(cwd, size) != NULL) {
      printf("Current working directory: %s\n", cwd);
      free(cwd);
      return 1;
    }

    if (errno == ERANGE) {
      size *= 2;
    } else {
      perror("shell");
      free(cwd);
      return 1;
    }
  }
}
