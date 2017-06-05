CC=sdcc -o build/ --std-sdcc99 -mmcs51

dist: build/main.ihx
	packihx build/main.ihx > dist/calc.hex

build/main.ihx: build/main.rel build/display.rel build/keyboard.rel \
	build/number.rel build/stack.rel build/constants.rel
	$(CC) build/main.rel build/display.rel build/keyboard.rel \
		build/number.rel build/stack.rel build/constants.rel

build/main.rel: src/main.c
	$(CC) -c src/main.c

build/display.rel: src/display.c
	$(CC) -c src/display.c

build/keyboard.rel: src/keyboard.c
	$(CC) -c src/keyboard.c

build/number.rel: src/number.c
	$(CC) -c src/number.c

build/stack.rel: src/stack.c
	$(CC) -c src/stack.c

build/constants.rel: src/constants.c
	$(CC) -c src/constants.c

clean:
	rm -f dist/*
	rm -f build/*
