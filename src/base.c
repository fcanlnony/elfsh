#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

#include "base.h"

extern int argc;
extern char *argv[25];

void input_print(char *input)
{
    const char NULL_char[] = " ";
    argv[0] = strtok(input,NULL_char);
    argv[1] = strtok(NULL,NULL_char);
}

int exec_cmd(char *input)
{
    pid_t pidN = fork();
    if(pidN < 0) {
	fprintf(stderr,"Error in fork");
	return -1;
    }
    else if(pidN == 0) {
	input_print(input);
	execvp(argv[0],argv);
	exit(0);
    } else {
	int status = wait(&status);
	if(WIFEXITED(status))
	    fprintf(stderr,"%d",WEXITSTATUS(status));
    }
    return 0;
}

