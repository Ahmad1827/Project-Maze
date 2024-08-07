#include "Map.h"
#include "game.h"
#include <fstream>
#include "TextureManager.h"


const Uint8* keystates = SDL_GetKeyboardState(NULL);
int keypressed[50];
int timepressed[50];
int level = 1, ok = 1,coincount=0;

int lvl1[20][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
					{0,0,1,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

int lvl2[20][25] = { {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
{3, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3},
{3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
{3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 3, 0, 3},
{3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 0, 3, 0, 3},
{3, 4, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0},
{3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 3},
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
};



int lvl3[20][25] = { {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
{3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{3, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 0, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3},
{3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3},
{3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 3, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3},
{3, 0, 3, 0, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 0, 3},
{3, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3},
{3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3},
{3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3},
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3} };
int lvl4[20][25] = { {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
{3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
{3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 3, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
{3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
{3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 0},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3},
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3} };
int lvl5[20][25] = { {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
{3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 3, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
{3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 0, 3},
{3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
{3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3},
{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 0},
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3} };

int lvl6[20][25] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

Map::Map()
{
	wall = TextureManager::LoadTexture("pics/wallmaze.png");
	floor = TextureManager::LoadTexture("pics/floormaze.png");
	player = TextureManager::LoadTexture("pics/playerwallmaze.png");
	obs = TextureManager::LoadTexture("pics/obsmaze.png");
	coin = TextureManager::LoadTexture("pics/coinmaze.png");
	coinage = TextureManager::LoadTexture("pics/coincountmaze.png");
	zero = TextureManager::LoadTexture("pics/zeromaze.png");
	one = TextureManager::LoadTexture("pics/onemaze.png");
	two = TextureManager::LoadTexture("pics/twomaze.png");
	three = TextureManager::LoadTexture("pics/threemaze.png");
	four = TextureManager::LoadTexture("pics/fourmaze.png");
	finaltext = TextureManager::LoadTexture("pics/finaltextmaze.png");
	floorplayer = TextureManager::LoadTexture("pics/playerfloormaze.png");



	LoadMap(lvl1);

	src2.x = src2.y = 0;
	dest2.x = dest2.y = 0;
	src2.w = dest2.w = 90;
	src2.h = dest2.h = 30;

	dest3.y = src3.y = 0;
	src3.x = 0;
	dest3.x = 95;
	src3.w = dest3.w = 30;
	src3.h = dest3.h = 30;

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;
	dest.x = dest.y = 0;

	src4.x = src4.y = 0;
	src4.h = 640;
	src4.w = 800;
	dest4.x = dest4.y = 0;
	dest4.w = 800;
	dest4.h = 640;

}

void Map::Updater()
{

	if (level == 2)
	{
		if (ok == level - 1)
		{
			LoadMap(lvl2);
			DrawMap();
			ok++;
		}
	}
	if (level == 3)
	{
		if (ok == level - 1)
		{
			LoadMap(lvl3);
			DrawMap();
			ok++;
		}
	}
	if (level == 4)
	{
		if (ok == level - 1)
		{
			LoadMap(lvl4);
			DrawMap();
			ok++;
		}
	}
	if (level == 5)
	{
		if (ok == level - 1)
		{
			LoadMap(lvl5);
			DrawMap();
			ok++;
		}
	}
	if (level == 6)
	{
		LoadMap(lvl6);
		DrawMap();
	}
	

	if (level == 6 && keystates[SDL_SCANCODE_R])
	{
		LoadMap(lvl1);
		DrawMap();
		level = 1;
		ok = 1;
		coincount = 0;
		for (int i = 0; i < 10; ++i)
		{
			timepressed[i] = 0;
			keypressed[i] = 0;
		}

	}
	for (int i = 0; i < 10; ++i)
	{
		if (keypressed[i] == 1)
		{
			timepressed[i]++;
			if (timepressed[i] >= 11)
			{
				keypressed[i] = 0;
				timepressed[i] = 0;
			}
		}
		else
		{
			timepressed[i] = 0;
		}
	}
	if (keystates[SDL_SCANCODE_RIGHT] && keypressed[0]==0)
	{
		int ok = 0;
		for (int row = 0; row < 20; ++row)
		{
			if (ok == 0)
			{
				for (int column = 0; column < 25; ++column)
				{
					if ((map[row][column] == 2 || map[row][column] == 5) && map[row][column+1]!=3)
					{
						int aux = map[row][column];
						std::cout << column << std::endl;
						if (column == 23)
						{
							std::cout << "ahmadddddd";
							level++;
						}
						if (map[row][column + 1] == 4)
						{
							map[row][column] = 0;
							coincount++;
							if (coincount == 1)
							{
								TextureManager::Draw(one, src3, dest3);
							}
							else if (coincount == 2)
							{
								TextureManager::Draw(two, src3, dest3);
							}
							else if (coincount == 3)
							{
								TextureManager::Draw(three, src3, dest3);
							}
							else if (coincount == 4)
							{
								TextureManager::Draw(four, src3, dest3);
							}
						}
						else
						{
							map[row][column] = map[row][column + 1];
						}
						if (map[row][column] == 0)
						{
							map[row][column + 1] = 2;
						}
						else
						{
							map[row][column + 1] = 5;
						}
						ok = 1;
						break;
					}
				}
			}
		}
		keypressed[0] = 1;
		DrawMap();
	}
	else if(keypressed[0]==1 && !keystates[SDL_SCANCODE_RIGHT])
	{
		keypressed[0] = 0;
	}
	if (keystates[SDL_SCANCODE_LEFT] && keypressed[1] == 0)
	{
		int ok = 0;
		for (int row = 0; row < 20; ++row)
		{
			if (ok == 0)
			{
				for (int column = 0; column < 25; ++column)
				{
					if ((map[row][column] == 2 || map[row][column] == 5) && map[row][column-1]!=3)
					{
						int aux = map[row][column];
						if (map[row][column - 1] == 4)
						{
							map[row][column] = 0;
							coincount++;
							if (coincount == 1)
							{
								TextureManager::Draw(one, src3, dest3);
							}
							else if (coincount == 2)
							{
								TextureManager::Draw(two, src3, dest3);
							}
							else if (coincount == 3)
							{
								TextureManager::Draw(three, src3, dest3);
							}
							else if (coincount == 4)
							{
								TextureManager::Draw(four, src3, dest3);
							}
						}
						else
						{
							map[row][column] = map[row][column - 1];
						}
						if (map[row][column] == 0)
						{
							map[row][column - 1] = 2;
						}
						else
						{
							map[row][column - 1] = 5;
						}
						ok = 1;
						break;
					}
				}
			}
		}
		keypressed[1] = 1;
		DrawMap();
	}
	else if (keypressed[1] == 1 && !keystates[SDL_SCANCODE_LEFT])
	{
		keypressed[1] = 0;
	}
	if (keystates[SDL_SCANCODE_UP] && keypressed[2] == 0)
	{
		int ok = 0;
			for (int row = 0; row < 20; ++row)
			{
				if (ok == 0)
				{
					for (int column = 0; column < 25; ++column)
					{
						if ((map[row][column] == 2 || map[row][column] == 5) && map[row-1][column]!=3)
						{
							int aux = map[row][column];
							if (map[row-1][column] == 4)
							{
								map[row][column] = 0;
								coincount++;
								if (coincount == 1)
								{
									TextureManager::Draw(one, src3, dest3);
								}
								else if (coincount == 2)
								{
									TextureManager::Draw(two, src3, dest3);
								}
								else if (coincount == 3)
								{
									TextureManager::Draw(three, src3, dest3);
								}
								else if (coincount == 4)
								{
									TextureManager::Draw(four, src3, dest3);
								}
							}
							else
							{
								map[row][column] = map[row-1][column];
							}
							if (map[row][column] == 0)
							{
								map[row-1][column] = 2;
							}
							else
							{
								map[row-1][column] = 5;
							}
							ok = 1;
							break;
						}
					}
				}
			}
		keypressed[2] = 1;
		DrawMap();
	}
	else if (keypressed[2] == 1 && !keystates[SDL_SCANCODE_UP])
	{
		keypressed[2] = 0;
	}

	if (keystates[SDL_SCANCODE_DOWN] && keypressed[3] == 0)
	{
		int ok = 0;
		for (int row = 0; row < 20; ++row)
		{
			if (ok == 0)
			{
				for (int column = 0; column < 25; ++column)
				{
					if ((map[row][column] == 2 || map[row][column] == 5) && map[row+1][column]!=3)
					{
						int aux = map[row][column];
						if (map[row+1][column] == 4)
						{
							map[row][column] = 0;
							coincount++;
							if (coincount == 1)
							{
								TextureManager::Draw(one, src3, dest3);
							}
							else if (coincount == 2)
							{
								TextureManager::Draw(two, src3, dest3);
							}
							else if (coincount == 3)
							{
								TextureManager::Draw(three, src3, dest3);
							}
							else if (coincount == 4)
							{
								TextureManager::Draw(four, src3, dest3);
							}

						}
						else
						{
							map[row][column] = map[row+1][column];
						}
						if (map[row][column] == 0)
						{
							map[row + 1][column] = 2;
						}
						else
						{
							map[row + 1][column] = 5;
						}
						ok = 1;
						break;
					}
				}
			}
		}
		keypressed[3] = 1;
		DrawMap();
	}
	else if (keypressed[3] == 1 && !keystates[SDL_SCANCODE_DOWN])
	{
		keypressed[3] = 0;
	}
}

void Map::LoadMap(int arr[20][25])
{
	for (int row = 0; row < 20; ++row)
	{
		for (int column = 0; column < 25; ++column)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 20; ++row)
	{
		for (int column = 0; column < 25; ++column)
		{
			type = map[row][column];
			dest.x = column * 32;
			dest.y = row * 32;
			TextureManager::Draw(coinage, src2, dest2);
			if (coincount == 0)
			{
				TextureManager::Draw(zero, src3, dest3);
			}
			else if (coincount == 1)
			{
				TextureManager::Draw(one, src3, dest3);
			}
			else if (coincount == 2)
			{
				TextureManager::Draw(two, src3, dest3);
			}
			else if (coincount == 3)
			{
				TextureManager::Draw(three, src3, dest3);
			}
			else if (coincount == 4)
			{
				TextureManager::Draw(four, src3, dest3);
			}
			if (level == 6)
			{
				TextureManager::Draw(finaltext, src4, dest4);
			}
			switch (type)
			{
			case 0:
				TextureManager::Draw(wall, src, dest);
				break;
			case 1:
				TextureManager::Draw(floor, src, dest);
				break;
			case 2:
				TextureManager::Draw(player, src, dest);
				break;
			case 3:
				TextureManager::Draw(obs, src, dest);
				break;
			case 4:
				TextureManager::Draw(coin, src, dest);
				break;
			case 5:
				TextureManager::Draw(floorplayer, src, dest);
				break;
			default:
				break;
			}

		}
	}
}

