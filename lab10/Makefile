build:
	gcc -Wall -Wextra -pthread inventory_fixed.c -o inventory_fixed

debug:
	gcc -g inventory.c -o inventory_fixed

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all ./inventory_fixed

clean:
	rm -f inventory_fixed
