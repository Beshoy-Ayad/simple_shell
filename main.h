#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_LEN 1024
#define PROMPT "P:> "
#define MAX_ARG 64
#define DELIM " \t\r\n\a "

char **command(char *line);
void Exec(char **argv);
int Exec1(char **argv);
void code_loop(void);
int main(void);

#endif
