executable: main.o functions.o doFunctions.o
	gcc main.o functions.o doFunctions.o -o executable
	
main.o: main.c header.h
	gcc -c main.c
	
doFunctions.o: doFunctions.c header.h
	gcc -c doFunctions.c
	
functions.o: functions.c header.h
	gcc -c functions.c
	
