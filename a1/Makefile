all: game_of_life test 

game_of_life: Game_Of_Life.c
	gcc -O3 -fopenmp -o Game_Of_Life Game_Of_Life.c
test: test.c
	gcc -O3 -o test test.c

clean: 
	rm Game_Of_Life *.out *.err test
