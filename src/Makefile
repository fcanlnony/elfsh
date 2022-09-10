cc = gcc -std=c11
cc_debug = ${cc} -g
headers = base.h define.h
name = elfsh
sources = base.c elfsh.c

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