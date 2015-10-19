all:
	gcc -Wall -ggdb -o output/komodo src/main.c src/engine.c
test:
	gcc -Wall -o output/komodo-test tst/komodo-tests.c tst/main.c src/engine.c -Isrc/ -lcunit
