#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <ctype.h>
#include <unistd.h>

#include "define.h"
#include "base.h"

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

int argc;
char *argv[25];

int main()
{
    char input[1024];
    while(1) {
        create();
	scanf("%[^\n]%*c",input);
	exec_cmd(input);
    }
}
