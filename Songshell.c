#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pwd.h>

#define MAX_LEN_LINE    100
#define LEN_HOSTNAME	30

int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
    char * welcome[17];
    printf("                         \n");
    welcome[0]="                    /^\\/^\\          ";
    welcome[1]="                  _|__|  O|     ";
    welcome[2]="         \\/     /~     \\_/ \\    ";
    welcome[3]="          \\____|__________/  \\  ";    
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
    welcome[16]="                        ~--______-~                ~-___-~\n";

    int picture;
    for(picture=0;picture<17;picture++){
        printf("%s",welcome[picture]);
        printf("\n");
    };
    
    char hostname[LEN_HOSTNAME + 1];
    memset(hostname, 0x00, sizeof(hostname));
    printf("\033[1;32m username:\033[0m \033[1;35m %s \033[0m \n", getpwuid(getuid())->pw_name);
    
    gethostname(hostname, LEN_HOSTNAME);
    printf("\033[1;32m hostname:\033[0m \033[1;35m %s \033[0m \n", hostname);

    
    
    struct tm *clock;
    time_t current;


    time(& current);

    clock=localtime(& current); 

    printf("현재시간 = %d시 %d분 %d초\n",clock->tm_hour%12,clock->tm_min,clock->tm_sec);
    printf("\n");
        
    while (true) {
        
        char *s;
        int len;
        
        printf("\033[1;34m SongShell $~\033[0m");
        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
                       
        command[strlen(command) - 1] = '\0'; 
        if(!strcmp("exit",command)) {
            printf("종료\n");
            exit(1);
        
            //break;
            //return -1;
        }
        
        if(strcmp(command,"ls") ==0){
            system("ls");
            continue;
        }
        
        if(strcmp(command,"clear")==0){
            system("clear");
            continue;
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
