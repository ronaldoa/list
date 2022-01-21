list: main.c slist.c mem.c interface.c sysconf.c test_slist.c
	gcc -g -o  main slist.c mem.c interface.c sysconf.c test_slist.c main.c 
clean:
	rm list
