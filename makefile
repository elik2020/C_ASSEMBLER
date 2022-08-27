assembler: main.o pre_assembler.o macro_table.o files.o first_pass.o general_functions.o operation_handler.o symbol_table.o directives_handler.o second_pass.o
		gcc -ansi -Wall -pedantic main.o pre_assembler.o macro_table.o files.o first_pass.o general_functions.o operation_handler.o symbol_table.o directives_handler.o second_pass.o -o assembler

pre_assembler.o: PreAssembler/pre_assembler.c PreAssembler/pre_assembler.h
		gcc -c -ansi -Wall -pedantic PreAssembler/pre_assembler.c -o pre_assembler.o

macro_table.o: PreAssembler/macro_table.c PreAssembler/macro_table.h
		gcc -c -ansi -Wall -pedantic PreAssembler/macro_table.c -o macro_table.o

files.o: Utility/files.c Utility/files.h
		gcc -c -ansi -Wall -pedantic Utility/files.c -o files.o

first_pass.o: Iterations/first_pass.c Iterations/first_pass.h 
		gcc -c -ansi -Wall -pedantic Iterations/first_pass.c -o first_pass.o

general_functions.o: Utility/general_functions.c Utility/general_functions.h 
		gcc -c -ansi -Wall -pedantic Utility/general_functions.c -o general_functions.o

operation_handler.o: Utility/operation_handler.c Utility/operation_handler.h 
		gcc -c -ansi -Wall -pedantic Utility/operation_handler.c -o operation_handler.o

symbol_table.o: Utility/symbol_table.c Utility/symbol_table.h 
		gcc -c -ansi -Wall -pedantic Utility/symbol_table.c -o symbol_table.o

directives_handler.o: Utility/directives_handler.c Utility/directives_handler.h 
		gcc -c -ansi -Wall -pedantic Utility/directives_handler.c -o directives_handler.o

second_pass.o: Iterations/second_pass.c Iterations/second_pass.h
		gcc -c -ansi -Wall -pedantic Iterations/second_pass.c -o second_pass.o

main.o: main.c main.h
		gcc -c -ansi -Wall -pedantic main.c -o main.o

		