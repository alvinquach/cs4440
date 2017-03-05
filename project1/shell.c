// Alvin Quach, 300793745
// CS4440 Spring 2017 Project 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LINE 255
#define HISTORY_SIZE 10

void add_history(char* history[], char* input, int* count) {

    int i;

    printf("Contents Before: \n");
    for (i = 0; i < HISTORY_SIZE; i++) {
        if (history[i] == NULL) break;
        printf("\t%i %s\n", i, history[i]);
    }
    printf("\n");
    printf("Count Before: %i\n", *count);

    // Store the issued command into the history array, removing the first value and shifting the rest of the values over if necessary.
    for (i = 0; i < HISTORY_SIZE; i++) {
        
        // If the history has already reached its limit, then copy the value from the next value.
        if (*count >= HISTORY_SIZE) {

            // If the index is not the last index, then copy the value from the next value.
            if (i < HISTORY_SIZE - 1) {
                strcpy(history[i], history[i + 1]);
            }

            // Copy the new command to the last index.
            else {
                strcpy(history[i], input);
            }
            
        }
        
        // If the history has not reached the limit, then copy the new command to the first available index.
        else if (!strcmp(history[i], "\0")) {
            strcpy(history[i], input);
            break;
        }

    }
    
    printf("Contents After: \n");
    for (i = 0; i < HISTORY_SIZE; i++) {
        if (history[i] == NULL) break;
        printf("\t%i %s\n", i, history[i]);
    }
    printf("\n");

    // Increment the history count.
    *count += 1;

}

int main(void) {

    char input[MAX_LINE];

    // Initialize command history array.
    int history_count = 0;
    char* history[HISTORY_SIZE];
    int i;
    for (i = 0; i < HISTORY_SIZE; i++) {
        history[i] = malloc(MAX_LINE);
        strcpy(history[i], "\0");
    }

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

        // TODO Detect "!!" and "!n" inputs.

        // Store user input in history, even if its an invalid command.
        add_history(history, input, &history_count);
        printf("Count After: %i\n", history_count);
        
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

            // Split input string by spaces.
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
