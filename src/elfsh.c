#include <ctype.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "base.h"
#include "define.h"
#include "argv.h"
#include "buildin.h"

static void create();

static void create()
{
    struct passwd *pwd = getpwuid(getuid());
    char path[100];
    getcwd(path,sizeof(path));
    if(strcmp(pwd->pw_name,"root"))
        printf("\001\033[1;;0m%s\002\001 [ %s ]\033[0m\002",pwd->pw_name,path);
    else printf("\001\033[1;;31m%s\033[0m\002\001 [ %s ]\002",pwd->pw_name,path);
}

void cat_sign(int signnum);

void cat_sign(int signnum)
{
    printf("\nSignal : %d\n",signnum);
}

char *argv[50] = {NULL};
char *argvA[10] = {NULL};
char *argvB[10] = {NULL};

static void input_print(char *input);
static void input_print(char *input)
{
    argv[0] = strtok(input," ");
    short i = 0;
    while(argv[i] != NULL)
	argv[++i] = strtok(NULL," ");
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
    signal(SIGINT,cat_sign);
    read_history(NULL);
    while (1) {
	char *input = malloc(sizeof(char)*1024);
	memset(input,0x00,1024);
	create();
	input = readline(" >>> ");
	add_history(input);
	if(strcmp(input,"") == 0)
	    continue;
	if (strcmp(input,"exit") == 0) {
	    exit(0);
        } else {
	    input_print(input);
            if(checkinside(argv) != -1)
		buildin(argv);
	    else exec_cmd(argv);
	}
	write_history(NULL);
	free(input);
    }
}
