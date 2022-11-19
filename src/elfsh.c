#include <ctype.h>
#include <pwd.h>
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
#include "env_funcs.h"

char *argv[50] = {NULL};
char *argvA[10] = {NULL};
char *argvB[10] = {NULL};

static void input_strtok(char *input);
static void input_strtok(char *input)
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
    struct passwd *pwd = getpwuid(getuid());
    char history_file[55];
    if(strcmp(pwd->pw_name,"root"))
	sprintf(history_file,"/home/%s/.elfsh_history",pwd->pw_name);
    else sprintf(history_file,"/root/.elfsh_history");
    read_history(history_file);
    while (1) {
	char path[100];
	getcwd(path,sizeof(path));
	char *readline_output_str = malloc(sizeof(char)*100);
	if(strcmp(pwd->pw_name,"root"))
	    sprintf(readline_output_str,"\033[1;;32m%s\033[0m\033[1;;32m [ \033[0m%s\033[1;;32m ]\033[0m\n>>> ",pwd->pw_name,path);
	else sprintf(readline_output_str,"\033[1;;31m%s\033[0m\033[1;;31m [ \033[0m%s\033[1;;31m ]\033[0m\n>>> ",pwd->pw_name,path);
	char *input = malloc(sizeof(char)*1024);
	memset(input,0x00,1024);
	input = readline(readline_output_str);
	add_history(input);
	if(strcmp(input,"") == 0)
	    continue;
	if (strcmp(input,"exit") == 0) {
	    exit(0);
        } else {
	    input_strtok(input);
            if(checkinside(argv) != -1)
		buildin(argv);
	    else if(check_env_cmd(argv[0]))
		run_env_cmd(argv);
	    else exec_cmd(argv);
	}
	write_history(history_file);
	free(input);
	free(readline_output_str);
    }
}
