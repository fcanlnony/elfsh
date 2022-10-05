#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "buildin.h"

short checkinside(char *charArray[])
{
    if(strcmp(charArray[0],"cd"))
	return -1;
    return 0;
}

static short cmd_cd(char *argv);
static short cmd_cd(char *argv)
{
    char cwd[100];
    if(strcmp(argv,"~") == 0) {
	struct passwd *pwd=getpwuid(getuid());
	chdir("/home");
	chdir(pwd->pw_name);
	return 0;
    } else if(access(argv,F_OK) == -1) {
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

void buildin(char *argv[])
{
    if(checkinside(argv) == 0)
	cmd_cd(argv[1]);
}
