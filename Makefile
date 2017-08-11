
pc: pc.c
	gcc -Wall -g -pthread pc.c -o pc

.PHONY: clean
clean:
	rm -rf pc
