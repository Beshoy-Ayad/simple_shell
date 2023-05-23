#ifndef MAIN_H
#define MAIN_H

#define MAX_INPUT_LENGTH 1024
#define MAXARGS 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>


void string_token(char *str, char *delimiter, char *argv[]);
void add_bin_prefix(char *argv[], char *new_arg);

void eval(char *cmdline);
int builtin_command(char **argv);
char *search_path(char *file);

#endif
