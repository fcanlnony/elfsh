cc = gcc -std=c11
cc_debug = ${cc} -g
headers = buildin.h base.h define.h argv.h
name = elfsh
sources = buildin.c base.c argv.c elfsh.c

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
