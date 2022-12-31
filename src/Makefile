cc = gcc -std=c11 -lreadline
cc_debug = ${cc} -g
headers = env_funcs.h buildin.h base.h define.h argv.h pipe_elfsh.h
name = elfsh
sources = env_funcs.c buildin.c base.c pipe_elfsh.c argv.c elfsh.c

all:
	${cc} ${headers} ${sources} -o ${name}

.PHONY : clean install uninstall with-debug

clean:
	rm elfsh

install:
	cp elfsh /bin/
	chmod 755 /bin/elfsh

uninstall:
	rm /bin/elfsh

with-debug:
	${cc_debug} ${headers} ${sources} -o ${name}
