all:
	g++ -I src/include -L src/lib -o main main.cpp ComFun.cpp BaseObject.cpp GameMap.cpp MainObject.cpp Timer.cpp NguyHiem.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	