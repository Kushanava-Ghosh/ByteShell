#include <stdio.h>
#include "echo.h"
#include "main.h"

int echo_message(char **args) {
  int i = 1;
  while (args[i] != NULL) {
    printf("%s ", args[i]);
    i++;
  }
  printf("\n");
  return 1;
}
