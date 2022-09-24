#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

#include "base.h"
#include "buildin.h"

extern char *argv[50];

void input_print(char *input)
{
    const char NULL_char[] = " ";
    argv[0] = strtok(input,NULL_char);
    short i = 0;
    while(argv[i] != NULL)
        argv[++i] = strtok(NULL,NULL_char);
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
        buildincmd(argv);
        exit(0);
    } else {
        int status = wait(&status);
        if(WIFEXITED(status))
            fprintf(stderr,"%d",WEXITSTATUS(status));
    }
    return 0;
}
