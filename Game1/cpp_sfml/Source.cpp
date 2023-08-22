#include <iostream>
#include "Game.h"

int main()
{

	// Initialize srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// Initialize Game Engine
	Game game;

	// Game Loop
	while (game.running() && !game.getEndgame())
	{
		// Update
		game.update();

		// Render
		game.render();
		
	}

	return 0;

}
