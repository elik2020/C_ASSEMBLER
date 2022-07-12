assembler: main.o pre_assembler.o macro_table.o files.o
		gcc -ansi -Wall -pedantic main.o pre_assembler.o macro_table.o files.o -o assembler

pre_assembler.o: pre_assembler.c pre_assembler.h
		gcc -c -ansi -Wall -pedantic pre_assembler.c -o pre_assembler.o

macro_table.o: macro_table.c macro_table.h
		gcc -c -ansi -Wall -pedantic macro_table.c -o macro_table.o

files.o: files.c files.h
		gcc -c -ansi -Wall -pedantic files.c -o files.o

main.o: main.c main.h
		gcc -c -ansi -Wall -pedantic main.c -o main.o