<<<<<<< HEAD
all: game_of_life test 

game_of_life: Game_Of_Life.c
	gcc -O3 -fopenmp -o Game_Of_Life Game_Of_Life.c
test: test.c
	gcc -O3 -o test test.c

clean: 
	rm Game_Of_Life *.out *.err test
=======
all: game_of_life game_of_life_gif 

game_of_life: Game_Of_Life.c
	gcc -O3 -fopenmp -o Game_Of_Life Game_Of_Life.c

game_of_life_gif: Game_Of_Life.c
	gcc -O3 -DOUTPUT -fopenmp -o Game_Of_Life_Gif Game_Of_Life.c
clean: 
	rm Game_Of_Life Game_of_Life_Gif *.out *.err *.gif
>>>>>>> 914d66d (Init)
