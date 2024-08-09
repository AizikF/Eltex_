#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 10

void parseInput(char* input, char** args) {
    int argCount = 0;
    char* token = strtok(input, " ");
    
    while (token != NULL && argCount < MAX_ARGS) {
        args[argCount++] = token;
        token = strtok(NULL, " ");
    }
    args[argCount] = NULL; 
}

int main() {
    char input[MAX_CMD_LEN];
    char* args[MAX_ARGS];

    while (1) {
        printf("> ");
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) break; 
        
        input[strcspn(input, "\n")] = '\0';
        
        parseInput(input, args);
        
        pid_t pid = fork();
        if (pid == -1) {
            perror("Ошибка при создании дочернего процесса");
            continue;
        } else if (pid == 0) {
            printf("Текущий рабочий каталог: %s\n", getcwd(NULL, 0)); 
            printf("Выполняется команда: %s\n", args[0]);
			char temp [64] ;
			strcpy(temp, "./");
			strcat(temp, args[0]);
            execvp(temp, args);
            perror("Ошибка при выполнении команды");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }

    return EXIT_SUCCESS;
}
