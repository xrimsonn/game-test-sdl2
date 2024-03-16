build: 
	mkdir -p ./bin
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o ./bin/game

run:
	./bin/game

clean:
	rm -rf ./bin

