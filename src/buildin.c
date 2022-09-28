#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "buildin.h"

short cmd_cd(char *argv)
{
    char cwd[100];
    if(access(argv,F_OK) == -1) {
	fprintf(stdout,"elfsh: cd :%s :Not such file or directory\n",argv);
	return -1;
    }
    if(chdir(argv) == -1) {
	fprintf(stdout, "elfsh: cd:%s :isn't a directory\n",argv);
	return -2;
    } else if(getcwd(cwd,sizeof(cwd)) == NULL)
	fprintf(stderr,"getcwd() error\n");
    return 0;
}
