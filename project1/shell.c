// Alvin Quach, 300793745
// CS4440 Spring 2017 Project 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

#define MAX_LINE 255
#define HISTORY_LIMIT 3


void add_history(char* history[], char* input, int* count) {

    int i;

    // Store the issued command into the history array, removing the first value and shifting the rest of the values over if necessary.
    for (i = 0; i < HISTORY_LIMIT; i++) {
        
        // If the history has already reached its limit, then copy the value from the next value.
        if (*count >= HISTORY_LIMIT) {

            // If the index is not the last index, then copy the value from the next value.
            if (i < HISTORY_LIMIT - 1) {
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

    // Increment the history count.
    *count += 1;

}


int main(void) {

    char input[MAX_LINE];

    // Initialize command history array.
    int history_count = 0;
    char* history[HISTORY_LIMIT];
    int i;
    for (i = 0; i < HISTORY_LIMIT; i++) {
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

        // Print command history if the user input was "history".
        if (!strcmp(input, "history")) {
            for (i = HISTORY_LIMIT - 1; i >= 0; i--) {
                if (!strcmp(history[i], "\0")) {
                    continue;
                }
                printf("%i %s\n", i + 1 + (history_count > HISTORY_LIMIT ? history_count - HISTORY_LIMIT : 0), history[i]);
            }
            continue;
        }

        // Handle "!!" input.
        else if (!strcmp(input, "!!")) {
            if (history_count == 0) {
                printf("No commands in history.");
            }
            else {
                strcpy(input, history_count > HISTORY_LIMIT ? history[HISTORY_LIMIT - 1] : history[history_count - 1]);
                printf("%s\n", input);
            }
        }

        // Handle "!n" input.
        else if (input[0] == '!' && isdigit(input[1])) {
            int n = atoi(&input[1]); // Parse number from input.
            if (n == 0 || n <= history_count - HISTORY_LIMIT || n > history_count) {
                printf("No such command in history.\n");
                continue;
            }
            else {
                strcpy(input, history[n - 1 - (history_count > HISTORY_LIMIT ? history_count - HISTORY_LIMIT : 0)]);
                printf("%s\n", input);
            }
        }

        // Store user input in history, even if its an invalid command. The "history" command is not stored.
        add_history(history, input, &history_count);
        
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
