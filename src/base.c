#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

#include "base.h"

int exec_cmd(char *argv[])
{
    pid_t pidN = fork();
    if(pidN < 0) {
	fprintf(stderr,"Error in fork");
	return -1;
    }
    else if(pidN == 0) {
	if(execvp(argv[0],argv) < 0)
	    fprintf(stderr, "elfsh : command : %s : could not found\n", argv[0]);
	exit(0);
    } else {
	int status = wait(&status);
	if(WIFEXITED(status))
	    fprintf(stderr,"%d",WEXITSTATUS(status));
    }
    return 0;
}

