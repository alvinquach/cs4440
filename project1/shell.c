// Alvin Quach, 300793745
// CS4440 Spring 2017 Project 1

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include  <sys/types.h>

#define MAX_LINE 255

int main(void) {

    char input[MAX_LINE];

    while (1) {
        
        // Print user input prompt.
        printf("osh>");

        // Get user input from stdin, and then flush stdin after.
        fgets(input, MAX_LINE, stdin); // Note that input ends with a newline character.
        fflush(stdin);

        // Get rid of the newline character at the end of the string.
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = 0;
        }

        // Terminate the program if the user input was "exit".
        if (!strcmp(input, "exit")) {
            printf("Exiting...\n");
            return 0;
        }
        
        // Fork a process.
        pid_t pid = fork();
        
        // If there was an error forking...
        if (pid < 0) {
            printf("Failed to fork new process. Exiting...");
            return 1;
        }

        // If the current process is parent...
        else if (pid > 0) {
            
            // If the user input did not end with an '&', then we have to wait for the child process to finish.
            if (input[strlen(input) - 1] != '&') {
                int status;
                waitpid(pid, &status, 0);
            }

        }

        // If the current process is child...
        else {

            char *path;
            char *argv[MAX_LINE / 2];
            //printf("%s", input);

            // Create a new string and copy the input to the new string.
            char input_copy[strlen(input) - 1];
            strcpy(input_copy, input);



            // Get rid of the '&' at the end of the string.
            if (input_copy[strlen(input_copy) - 1] == '&') {
                input_copy[strlen(input_copy) - 1] = 0;
            }

            int count = 0;
            while(1) {
                char *arg;
                if (!count) {
                    arg = strtok(input_copy, " ");
                    path = arg;
                }
                else {
                    arg = strtok(NULL, " ");
                }
                if (arg == NULL) {
                    argv[count] = NULL;
                    break;
                }
                // printf("\t%s\n", arg);
                argv[count++] = arg;
            }

            // Excecute new process.
            execvp(path, argv);

            // If the execvp failed, then manually exit the fork.
            printf("Failed to execute command '%s'.\n", path);
            return 1;

        }

    }
    return 0;
}


