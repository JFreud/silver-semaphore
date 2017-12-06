all: sema.c
	gcc -o control sema.c
clean:
	rm a.out
	rm *~
run: all
ifeq ($(arg),c)
	./control -$(arg) $(n)
else
	./control -$(arg)
endif
