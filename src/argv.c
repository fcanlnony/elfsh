#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "argv.h"

static void help_cmd();

static void help_cmd()
{
    printf("--version show the elfsh version\n");
}

void argv_command(char *argv[])
{
    if(strcmp(argv[1],"--version") == 0)
	fprintf(stdout, "elfsh , version 0.0.2\n");
    else if(strcmp(argv[1],"--help") == 0)
	help_cmd();
    else fprintf(stdout, "elfsh : --help to get the information.\n");
}
