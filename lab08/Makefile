build:
	gcc -Wall -Wextra caseconv.c -o caseconv

debug:
	gcc -g caseconv.c -o caseconv

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all ./caseconv

clean:
	rm -f caseconv
