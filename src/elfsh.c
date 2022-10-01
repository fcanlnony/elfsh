#include <ctype.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "base.h"
#include "define.h"
#include "argv.h"
#include "buildin.h"

static void getUsername();

static void getUsername()
{
    struct passwd *pwd;
    pwd=getpwuid(getuid());
    if(strcmp(pwd->pw_name,"root") == 0)
        printf("\033[1;;31m%s\033[0m",pwd->pw_name);
    else printf("\033[1;;0m%s\033[0m",pwd->pw_name);
}

static void getPath();

static void getPath()
{
    char path[100];
    getcwd(path,sizeof(path));
    printf("%s",path);
}

void create();

void create()
{
    getUsername();
    printf(" [ ");
    getPath();
    printf(" ] >>> ");
}

void cat_sign(int signnum)
{
    printf("\nSignal : %d\n",signnum);
}

char *argv[50];

void input_print(char *input)
{
    const char NULL_char[] = " ";
    argv[0] = strtok(input,NULL_char);
    short i = 0;
    while(argv[i] != NULL)
	argv[++i] = strtok(NULL,NULL_char);
}

int main(int argc,char *argvm[])
{
    if(argc == 2) {
	argv_command(argvm);
	return 0;
    }
    if(argc > 2) {
	if(strcmp(argvm[1],"--run") == 0) {
	    if(argc >= 4) {
		fprintf(stderr,"Too many parameters.\n");
		exit(1);
	    }
	    char *t[2];
	    t[0] = "sh";
	    t[1] = argvm[2];
	    execv("/bin/sh",t);
	}
	else {
	    fprintf(stderr, "Not such option or too many parameters.\n");
	    exit(1);
	}
    }
    char input[1024];
    char exit_sign[]="exit";
    signal(SIGINT,cat_sign);
    while (1) {
	create();
        scanf("%[^\n]%*c",input);
        if (strcmp(input, exit_sign) == 0) {
            exit(0);
        } else {
	    input_print(input);
            if(checkinside(argv) == 0)
		cmd_cd(argv[1]);
	    else exec_cmd(argv);
	}
    }
}
