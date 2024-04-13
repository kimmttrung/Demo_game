#pragma once

#include "ComFun.h"
#include "BaseObject.h"

#define MAX_TILES 20 // chiều ngang 20 ô của map 

class TileMat : public BaseObject
{
    public:
        TileMat() {;}
        ~TileMat() {;}

};

class GameMap
{
    public:
        GameMap() {;}
        ~GameMap() {;}

        void LoadMap(char* name);// load map từ file
        void LoadTiles(SDL_Renderer* screen);// load hình ảnh cho map
        void DrawMap(SDL_Renderer* screen);// vẽ map


    private:
        Map game_map_;
        TileMat tile_mat[MAX_TILES];
};
    