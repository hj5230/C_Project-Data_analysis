project: project.o library.o
	gcc project.o library.o -o project
library.o: library.c
	gcc -c library.c
project.o: project.c
	gcc -c project.c