#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;
  int status;
  char *words[100];
  int n;
  char *token;
  char *path;
  char *full_path;
  int i;
  pid_t pid;

  while (1) {
    printf(">>> ");
    getline(&line, &len, stdin);

    if (strcmp(line, "exit") == 0) {
      free(line);
      break;
    } else if (strcmp(line, "env") == 0) {
      /* Print the current environment. */
      extern char **environ;
      char **envp = environ;
      while (*envp != NULL) {
        printf("%s=%s\n", *envp, *(envp + 1));
        envp += 2;
      }
    } else {
      /* Split the line into words. */
      n = 0;
      token = strtok(line, " ");
      while (token != NULL) {
        words[n++] = token;
        token = strtok(NULL, " ");
      }

      /* Check if the command exists. */
      path = getenv("PATH");
      if (path == NULL) {
        printf("Error: PATH environment variable not set.\n");
        continue;
      }

      full_path = NULL;
      for (i = 0; i < n; i++) {
        full_path = malloc(strlen(path) + strlen(words[i]) + 2);
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, words[i]);

        if (access(full_path, F_OK) != -1) {
          break;
        }

        free(full_path);
        full_path = NULL;
      }

      /* If the file does not exist, print an error message. */
      if (full_path == NULL) {
        printf("Error: Command '%s' not found.\n", words[0]);
        continue;
      }

      /* Fork a child process to execute the command. */
      pid = fork();
      if (pid == 0) {
        execve(full_path, words, NULL);
        printf("Error: Failed to execute command '%s'.\n", words[0]);
        exit(1);
      }

      /* In the parent process, wait for the child process to finish. */
      wait(&status);

      /* Free the memory allocated for the full path. */
      free(full_path);
    }
  }

  free(line);
  return 0;
}

