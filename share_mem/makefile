all : exe

exe : share_mem.o pipe_notify.o
	gcc -o exe share_mem.o pipe_notify.o
share_mem.o : share_mem.c pipe_notify.h
	gcc -c share_mem.c
pipe_notify.o: pipe_notify.c pipe_notify.h
	gcc -c pipe_notify.c
clean : 
	rm -f *.o

