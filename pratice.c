#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LEN_LINE    100
void cd(char *d);
void cd(char *d){
	char * name = "PWD"; //string PWD
  	char cwd[256]; // holder for current directory
  	char * newCurrent = getcwd(cwd, sizeof(cwd)); //get the current dir and put it in cwd

  	chdir(d); // change the directory
  	setenv(name, newCurrent,1); //set new pwd
}	

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
          if(strcmp(command,"clear")==0){
		  system("clear");
	  }
	 
     
	   len = strlen(command);  

	   printf("%d\n", len);
                  
	   if (command[len - 1] == '\n') {
	   	command[len - 1] = '\0'; 
	   }
 
	   printf("[%s]\n", command);
      
	   if (!strcmp(command,"cd")) { //change directory
           	cd(command); //call the helper function
            	continue;
           }	      
 
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
	    if (execlp(command,command,NULL)== -1){
		    printf("Command is failed\n");
		    exit(0);
	    }
        } 
    }
    return 0;
}


     


