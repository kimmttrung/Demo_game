all:
	g++ -I src/include -L src/lib -o main main.cpp func.cpp BaseObject.cpp GameMap.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	