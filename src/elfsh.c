#include <ctype.h>
#include <curses.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <unistd.h>

#include "base.h"
#include "define.h"

static void getUsername();

static void getUsername()
{
    struct passwd *pwd;
    pwd=getpwuid(getuid());
    if(strcmp(pwd->pw_name,"root") == 0)
        printf("\033[1;;31m%s\033[0m",pwd->pw_name);
    else printf("\033[1;;32m%s\033[0m",pwd->pw_name);
}

static void getPath();

static void getPath()
{
    char path[100];
    getcwd(path,sizeof(path));
    printf("%s",path);
}

static void create();

static void create()
{
    getUsername();
    printf(" \033[34;1m[\033[0m ");
    getPath();
    printf(" \033[34;1m]\033[0m >>> ");
}

void cat_sign(int signnum)
{
	int columns_long;

    setupterm(NULL, fileno(stdout), (int *)0);
	columns_long = tigetnum("cols")-12;
    char errput[columns_long];
	sprintf(errput, "\n\033[31;1mSignal : %d", signnum);
	for (int i=0;i<columns_long;i++)
	{
			strcat(errput, " ");
	}

	strcat(errput, ":(\033[0m\n");
    printf("%s",errput);
}

char *argv[50];

int main()
{
    char input[1024];
    char exit_sign[]="exit";
    while (1) {
        signal(SIGINT,cat_sign);
        create();
        scanf("%[^\n]%*c",input);
        if (!strcmp(input, exit_sign)) {
            exit(0);
        } else {
            exec_cmd(input);
        }
    }
}
