#include <dirent.h>
#include <stdio.h>
#include "ls.h"
#include "main.h"

int list_files(char **args) {
  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir(".")) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      printf("%s\n", ent->d_name);
    }
    closedir(dir);
  } else {
    perror("shell");
  }

  return 1;
}
