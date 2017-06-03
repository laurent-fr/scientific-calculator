CC=sdcc -o build/ --std-sdcc99 -mmcs51

dist: build/main.ihx
	packihx build/main.ihx > dist/calc.hex

build/main.ihx: build/main.rel build/display.rel build/keyboard.rel
	$(CC) build/main.rel build/display.rel build/keyboard.rel

build/main.rel: src/main.c
	$(CC) -c src/main.c

build/display.rel: src/display.c
	$(CC) -c src/display.c

build/keyboard.rel: src/keyboard.c
	$(CC) -c src/keyboard.c

clean:
	rm -f dist/*
	rm -f build/*