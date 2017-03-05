// Alvin Quach, 300793745
// CS4440 Spring 2017 Project 1

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80

int main(void) {

    int maxLength = MAX_LINE/2 + 1; // WTF?
    
    int should_run = 1;

    while (should_run) {

        char input[255];
        printf("osh>");
        fgets(input, 255, stdin); // Note that input ends with a newline character.
        fflush(stdin);

        // Terminate the program if the user input was "exit".
        if (!strcmp(input, "exit\n")) {
            printf("Exiting...\n");
            return 0;
        }

        char *path;
        char *argv[127];
        //parse_input(argv, input);
        //char *test[] = {"cd", "-l", NULL};

        printf("%s", input);

        // Create a new string and copy the input to the new string.
        char input_copy[strlen(input) - 1];
        strcpy(input_copy, input);

        // Get rid of the newline character at the end of the string.
        if (input_copy[strlen(input_copy) - 1] == '\n') {
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
            printf("\t%s\n", arg);
            argv[count++] = arg;
        }

        execvp(path, argv);

        /** * After reading user input, the steps are:

        * (1) fork a child process using fork()

        * (2) the child process will invoke execvp()

        * (3) if command included &, parent will invoke wait()

        */
    }
    return 0;
}


