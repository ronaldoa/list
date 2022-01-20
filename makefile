list: main.c slist.c mem.c interface.c sysconf.c
	gcc -g -o  list main.c slist.c mem.c interface.c sysconf.c 
clean:
	rm list
