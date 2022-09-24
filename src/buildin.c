#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "buildin.h"

char *argvB[10][5];

static short checkpipeNum(char *argv[]);

static short checkpipeNum(char *argv[])
{
    short i = 0;
    while(argv[++i]!= NULL) {
	if(strcmp(argv[i],"|") == 0) {
	    return 1;
	}
    }
    return 0;
}

static void dpipe(char *argv[]);

static void dpipe(char *argv[])
{
    short i = 0;
    short j = 0,l = 0;
    while(argv[i] != NULL) { 
	while(strcmp(argv[i++],"|")) {
	    argvB[j][l++] = argv[i];
	}
	argvB[++j][l] = argv[++i];
    }
}

static short checkinside(char *charArray[]);

static short checkinside(char *charArray[])
{
    if(strcmp(charArray[0],"cd"))
	return -1;
    return 0;
}

static short cmdfound(char *argv[]);

static short cmdfound(char *argv[])
{
    const char cutChar[] = ":";
    FILE *fp = fopen("/etc/elfsh/path","r");
    char *PATH[30],tmpREAD[1024];
    fscanf(fp,"%s",tmpREAD);
    char *input;
    input = tmpREAD;
    PATH[0] = strtok(input,cutChar);
    short num = 0;
    while(PATH[num] != NULL)
	PATH[++num] = strtok(NULL,cutChar);
    short i = checkpipeNum(argv),k = 0;
    short l = sizeof(PATH) / sizeof(PATH[0]),lp = 0;
    while(k <= i) {
	while(lp <= l) {
	    if(checkinside(argvB[k]) == -1)
		if(access(argvB[k][0],F_OK) == 0)
		    break;
	    if(PATH[lp] == NULL) {
		printf("elfsh: %s: commond not found",argvB[k][0]);
		return -1;
		}
	}
	k++;
    }
    return 0;
}

static short cmd_cd(char *argv);

static short cmd_cd(char *argv)
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

int buildincmd(char *argv[])
{
    short i = checkpipeNum(argv),k = 0,l = 0;
    if(i > 0) {
	dpipe(argv);
	while(k <= i) {
	    if(cmdfound(argvB[k]) == -1)
		return -1;
	    if(checkinside(argvB[k]) == 0) {
		cmd_cd(argvB[k][++l]);
		continue;
	    }
	    else {
		execvp(argvB[k][l],argvB[k]);
		continue;
	    }
	    k++;
	}
    }
    else if(i == 0) {
	if(checkinside(argv) == 0)
	    cmd_cd(argv[1]);
	else execvp(argv[0],argv);
	}
    return 0;
}
