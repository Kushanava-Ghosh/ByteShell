#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#include "cd.h"
#include "help.h"
#include "exit.h"
#include "ls.h"
#include "echo.h"
#include "pwd.h"
#include "myprint.h"
#include "history.h"
#include "alias.h"

int execute_command(char **args);

void print_centered(const char* text);
void print_horizontal_line(int width);
char **split_line(char *line);

char *builtin_commands[] = {
  "cd",
  "help",
  "exit",
  "ls",
  "echo",
  "pwd",
  "history",
  "alias",
  "show_aliases",
  "unalias"
};

int (*builtin_functions[]) (char **) = {
  &change_directory,
  &show_help,
  &exit_shell,
  &list_files,
  &echo_message,
  &print_working_directory,
  &print_history,
  &add_alias,
  &show_aliases,
  &unalias
};

int num_builtins() {
  return sizeof(builtin_commands) / sizeof(char *);
}

int launch_process(char **args) {
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("shell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("shell");
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int execute_command(char **args) {
  int i;

  if (args[0] == NULL) {
    return 1;
  }

  for (i = 0; i < num_builtins(); i++) {
    if (strcmp(args[0], builtin_commands[i]) == 0) {
      add_to_history(args);
      return (*builtin_functions[i])(args);
    }
  }
    // Check if the command is an alias
  char *command = replace_alias(args[0]);
  if (command != NULL) {
    char **alias_args = split_line(command);
    int status = execute_command(alias_args);
    free(alias_args);
    free(command);
    return status;
  }

  if (access(args[0], X_OK) == -1) {
    fprintf(stderr, "shell: unrecognized command: %s\n", args[0]);
    return 1;
  }

  return launch_process(args);
}

char *read_line(void)
{
  int bufsize = 1024;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "shell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += 1024;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

char **split_line(char *line)
{
  int bufsize = TOKEN_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "shell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TOKEN_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += TOKEN_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        free(tokens_backup);
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TOKEN_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

void shell_loop(void) {
    
    initialize_history(); 

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminal_width = w.ws_col;
    print_horizontal_line(terminal_width);

    // Print the centered welcome message
    const char* welcome_text = "Welcome to MASH (My Awesome Shell)!";
    print_centered(welcome_text);
    const char* help_text= "Feel free to use 'help' to see which built-ins are available.";
    print_centered(help_text);
    // Print a horizontal line
    print_horizontal_line(terminal_width);

    

    const char* print_test ="Testing myprint function";
    print_centered(print_test);
    myprint("Integer: %d\n", 10);
    myprint("Character: %c\n", 'H');
    myprint("String: %s\n", "Yeah Boi");
    print_horizontal_line(terminal_width);
    

    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = read_line();
        args = split_line(line);
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);
}

void print_centered(const char* text) {
    int width = strlen(text);
    int terminal_width;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    terminal_width = w.ws_col;

    int padding = (terminal_width - width) / 2;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    printf("%s\n", text);
}

void print_horizontal_line(int width) {
    for (int i = 0; i < width; i++) {
        printf("-");
    }
}

int main(int argc, char **argv) {
    initialize_history();
    initialize_alias_table();
    shell_loop();
    return EXIT_SUCCESS;
}
