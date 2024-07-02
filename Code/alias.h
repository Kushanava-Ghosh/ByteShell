#ifndef ALIAS_H
#define ALIAS_H

void initialize_alias_table();
int add_alias(char **args);
int show_aliases(char **args);
int unalias(char **args);
char* replace_alias(char *command);

#endif /* ALIAS_H */
