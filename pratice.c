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
          char *s;
          int len;
      
          printf("MyShell $ ");
       
          s = fgets(command, MAX_LEN_LINE, stdin);
                
          command[strlen(command) - 1] = '\0'; 
                     
        
          if (s == NULL) {      
              fprintf(stderr, "fgets failed\n");       
              exit(1);        
          }
        
          if(!strncmp(command, "exit", strlen(command))) {
                       return -1;        
          }         
            //break;
            //return -1        
          len = strlen(command);
          printf("%d\n", len);
          
          if (strcmp(command, "cd") == 0) { // cd 명령어인 경우
		       
              if (chdir(command) == -1) { // 디렉토리를 바꿔주고 리턴
			   
                  fatal("change directory fail");		
              }              		
              return 0;	          
          }



      }
}
