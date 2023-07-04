#include <iostream>

#include "Game.h"
#include "MenuState.h"
#include "Screen.h"
#include "SDL_net.h"

std::unique_ptr<Game> game = std::make_unique<Game>(new MenuState);

int main(int i, char* v[])
{
	if (game->Initialize())
	{
		game->Run();
		game->Shutdown();
	}
	return 0;
}