main:
	gcc -o lls main.c -Wall -Wextra -std=c99  --pedantic

clean:
	rm -f lls.exe c_ls.o main.o main.exe
