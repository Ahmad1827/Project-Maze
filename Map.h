#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Map {
public:
	Map();
	

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void Updater();
private:
	SDL_Rect src, dest, src2, dest2, src3, dest3,src4,dest4;
	SDL_Texture* wall;
	SDL_Texture* floor;
	SDL_Texture* player;
	SDL_Texture* floorplayer;
	SDL_Texture* obs;
	SDL_Texture* coin;
	SDL_Texture* coinage;
	SDL_Texture* zero;
	SDL_Texture* one;
	SDL_Texture* two;
	SDL_Texture* three;
	SDL_Texture* four;
	SDL_Texture* finaltext;
	int map[20][25];
};