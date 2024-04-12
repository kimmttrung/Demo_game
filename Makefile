all:
	g++ -I src/include -L src/lib -o main main.cpp Engine.cpp Texture.cpp Warrior.cpp Animation.cpp Input.cpp Timer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	