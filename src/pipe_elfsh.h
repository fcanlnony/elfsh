#ifndef PIPE_ELFSH_H_
#define PIPE_ELFSH_H_

extern int check_pipe(char *__string__);
extern void pipe_strtok(char *__string__,char **arrayA,char **arrayB);
extern int pipe_cmd(char **argvA,char **argvB);

#endif /*PIPE_ELFSH_H_*/
