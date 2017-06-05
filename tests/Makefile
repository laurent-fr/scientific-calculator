CC=gcc

testsuite: clean prepare tests
	./testsuite

prepare:
	cp ../src/number.* .
	cp ../src/display.* .
	cp ../src/stack.* .
	cp ../src/constants.* .
	for f in `ls -1 *.[c,h]` ; do \
	sed -i 's/__[^ ]* //g' $$f ; \
	sed -i '/#define IS_TARGET/d' $$f ; \
	done

tests: test.o number.o display.o stack.o constants.o
	$(CC) -o testsuite test.o number.o display.o stack.o constants.o

number.o: number.c
	$(CC) -c number.c

display.o: display.c
	$(CC) -c display.c

constants.o: constants.c
	$(CC) -c constants.c

test.o: test.c
	$(CC) -c test.c

clean:
	rm -f *.o
	rm -f number.c number.h display.c display.h stack.c stack.h constants.c constants.h
	rm -f testsuite
