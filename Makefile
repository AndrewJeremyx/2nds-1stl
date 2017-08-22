#Make File to linearForm

laba : main.o linearform.o int.o float.o linearspace.o
	gcc -o laba *.o
main.o : main.c
	gcc -c main.c
linearform.o : linearform.c
	gcc -c linearform.c
int.o : int.c
	gcc -c int.c
float.o : float.c
	gcc -c float.c
linearspace.o : linearspace.c
	gcc -c linearspace.c
clean :
	rm -f *.o laba

	
