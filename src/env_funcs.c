#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env_funcs.h"

short check_env_cmd(char *input)
{
    if(strncmp(input, ":", 1))
	return 0;
    else return 1;
}

void run_env_cmd(char **argv)
{
    if(strcmp(argv[0],":env") == 0)
    {
	if(strcmp(argv[2],"show") == 0) {
		if(strcmp(argv[3],"NULL") == 0)
		    printf("%s\n",getenv(argv[1]));
	} else _exit(0);
    }
    else if(strcmp(argv[2],"add") == 0) {
	if(strcmp(argv[4],"NULL") == 0)
	    setenv(argv[1],argv[3],1);
	else _exit(0);
    }
}
