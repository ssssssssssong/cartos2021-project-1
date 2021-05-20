#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LEN_LINE    100

int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
    
    while (true) {
        char * welcome[17];
        printf("                Happy Chinese Lunar New Year!                                            \n");
        welcome[0]="                    /^\\/^\\      1     ";
        welcome[1]="                  _|__|  ;
        welcome[2]="         \\/     /~     \\_/ \\     ";
        welcome[3]="          \\____|__________/  \\  3";    
        welcome[4]="                 \\_______      \\";
        welcome[5]="                         `\\     \\                 \\";
        welcome[6]="                           |     |                  \\";

        welcome[7]="                          /      /                    \\";
        welcome[8]="                         /     /                      \\\\";
        welcome[9]="                       /      /                         \\ \\";

        welcome[10]="                      /     /                            \\  \\";

        welcome[11]="                    /     /             _----_            \\   \\";
        welcome[12]="                   /     /           _-~      ~-_         |   |";
        welcome[13]="                  (      (        _-~    _--_    ~-_     _/   |";
        welcome[14]="                   \\      ~-____-~    _-~    ~-_    ~-_-~    /";
        welcome[15]="                     ~-_           _-~          ~-_       _-~   ";
        welcome[16]="                        ~--______-~                ~-___-~";

        char *s;
        int len;
        
        printf("SongShell $ ");
        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        
        len = strlen(command);
        printf("%d\n", len);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        
        printf("[%s]\n", command);
      
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
            printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }
        else {  /* child */
            ret = execve(args[0], args, NULL);
            if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
        } 
    }
    return 0;
}
