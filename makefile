run: compile
	@./JPJR.exe

compile:
	@g++ game.cpp -o JPJR.exe -Wall -std=c++17 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

clean:
	@rm *.exe
