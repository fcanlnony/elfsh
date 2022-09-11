#include <ctype.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    else printf("\033[1;;0m%s\033[0m",pwd->pw_name);
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
    printf(" [ ");
    getPath();
    printf(" ] >>> ");
}

void cat_sign(int signnum)
{
    char errput[1024];
    sprintf(errput,"\n\033[31mSignal : %d \t\t\t\t\t:(\n\033[0m",signnum);
    printf("%s",errput);
}

int argc;
char *argv[25];

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
