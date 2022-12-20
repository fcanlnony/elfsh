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
    if(strcmp(argv[0],":env") == 0) {
	if(strcmp(argv[2],"show") == 0) {
	    const char *tmp = getenv(argv[1]); 
	    puts(tmp);
	} else if(strcmp(argv[2],"add") == 0) {
		char *tmp = malloc(1024*sizeof(char));
		sprintf(tmp,"%s=%s",argv[1],argv[3]);
		putenv(tmp);
	} else if(strcmp(argv[2],"remove") == 0) {
	    unsetenv(argv[1]);
	}
	else printf("':env' : invalid option : '%s'\n", argv[2]);
    } 
}
