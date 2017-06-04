CC=gcc

testsuite: clean prepare tests
	./testsuite

prepare:
	cp ../src/number* .
	cp ../src/display* .
	for f in `ls -1 *.[c,h]` ; do \
	sed -i 's/__[^ ]* //g' $$f ; \
	sed -i '/#define IS_TARGET/d' $$f ; \
	done

tests: test.o number.o display.o
	$(CC) -o testsuite test.o number.o display.o

number.o: number.c
	$(CC) -c number.c

display.o: display.c
	$(CC) -c display.c

test.o: test.c
	$(CC) -c test.c

clean:
	rm -f *.o
	rm -f number.c number.h display.c display.h
	rm -f testsuite
