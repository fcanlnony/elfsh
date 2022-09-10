all:
	cd src/ && make

.PHONY : clean install uninstall

clean:
	cd src/ && make clean

install:
	cd src/ && make install

uninstall:
	cd src/ && make uninstall

