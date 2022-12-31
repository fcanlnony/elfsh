#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

#include "pipe_elfsh.h"

int check_pipe(char *__string__)
{
    char *string = malloc(1024*sizeof(char));
    strcpy(string,__string__);
    if(strchr(string,'|') != NULL)
	return 1;
    else return 0;
}

void pipe_strtok(char *__string__,char **arrayA,char **arrayB)
{
    char *string = malloc(1024*sizeof(char));
    memset(string,0x00,1024);
    strcpy(string,__string__);
    char *array_string[2] = {NULL};
    array_string[0] = strsep(&string,"|");
    array_string[1] = strsep(&string,"|");
    short i = 0,k = 0;
    while(arrayA[i] != NULL)
	arrayA[i++] = strsep(&array_string[0]," ");
    while(arrayB[k] != NULL)
	arrayB[k++] = strsep(&array_string[1]," ");
}

int pipe_cmd(char **argvA,char **argvB)
{
    int pipefd[2];
    if(pipe(pipefd) == -1) {
	puts("Error in pipe()");
	return -1;
    }

    pid_t p1, p2;
    p1 = fork();
    if(p1 < 0) {
	fprintf(stderr,"Error in fork");
	return -1;
    }
    else if(p1 == 0) {
	close(pipefd[0]);
	dup2(pipefd[1],STDOUT_FILENO);
	close(pipefd[1]);

	if(execvp(argvA[0],argvA) < 0) {
	    fprintf(stderr, "elfsh : command : %s : could not found\n", argvA[0]);
	    return -3;
	}
    } else if(p1 > 0) {
	p2 = fork();
	if(p2 < 0) {
	    fprintf(stderr,"Error in fork");
	    return -1;
	}
	close(pipefd[1]);
	dup2(pipefd[0],STDOUT_FILENO);
	close(pipefd[0]);

	if(execvp(argvB[0],argvB) < 0) {
	    fprintf(stderr, "elfsh : command : %s : could not found\n", argvB[0]);
	    return -3;
	}
    } else {
	wait(NULL);
	wait(NULL);
    }
    return 0;
}

