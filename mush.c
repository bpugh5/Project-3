#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    const char delimiter[] = " \n\t\r";
    char *token;
    int forkCheck;
    int chdirValue;

    while(1) {
        char userString[2048] = {};
        char* tokenStorage[128] = {};
        int count = 0;
        printf("MUSH $ ");
        fgets(userString, 2048, stdin);
        token = strtok(userString, delimiter);

        while(token != NULL) {
            tokenStorage[count] = token;
            count++;
            token = strtok(NULL, delimiter);
        }
        tokenStorage[count] = NULL;

        if (strcmp(tokenStorage[0], "cd") == 0) {
            chdirValue = chdir(tokenStorage[1]);
            if (chdirValue == -1) {
                perror("directory");
            }
            continue;
        }

        if(strcmp(tokenStorage[0], "exit") == 0) {
            exit(0);
        }

        forkCheck = fork();
        
        if (forkCheck == 0) {
            execvp(tokenStorage[0], tokenStorage);
            perror("exec");
            exit(1);
        }
        wait(NULL);
    }
}