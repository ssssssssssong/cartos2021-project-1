#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#define MAX_LEN_LINE    100
#define LEN_HOSTNAME	30
int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
    char hostname[LEN_HOSTNAME + 1];
    memset(hostname, 0x00, sizeof(hostname));
    printf("\033[1;32m username:\033[0m 033[1;31m %s \033[0m \n", getpwuid(getuid())->pw_name);

    gethostname(hostname, LEN_HOSTNAME);
    printf("\033[1;32m hostname:\033[0m 033[1;31m %s \033[0m \n", hostname);

    
	
	
	
    while (true) {
          char *s;
          int len;
      
          printf("\033[1;34m MyShell $~\033[0m");
          //printf("\033[1;33m Warning Warning~\033[0m");
          s = fgets(command, MAX_LEN_LINE, stdin);
                
          command[strlen(command) - 1] = '\0'; 
                     
        
          if (s == NULL) {      
              fprintf(stderr, "fgets failed\n");       
              exit(1);        
          }
        
          if(!strncmp(command, "exit", strlen(command))) {
                       return -1;        
     
	  }         
          if(strcmp(command,"clear")==0){
		  system("clear");
		  continue;
	  }
	  if(strcmp(command,"ls")==0){
		  system("ls");
		  continue;
	  }
	  if(strcmp(command,"cd")==0){
		  system("cd");
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


     


