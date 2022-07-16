assembler: main.o pre_assembler.o macro_table.o files.o
		gcc -ansi -Wall -pedantic main.o pre_assembler.o macro_table.o files.o -o assembler

pre_assembler.o: PreAssembler/pre_assembler.c PreAssembler/pre_assembler.h
		gcc -c -ansi -Wall -pedantic PreAssembler/pre_assembler.c -o pre_assembler.o

macro_table.o: PreAssembler/macro_table.c PreAssembler/macro_table.h
		gcc -c -ansi -Wall -pedantic PreAssembler/macro_table.c -o macro_table.o

files.o: Utility/files.c Utility/files.h
		gcc -c -ansi -Wall -pedantic Utility/files.c -o files.o

main.o: main.c main.h
		gcc -c -ansi -Wall -pedantic main.c -o main.o