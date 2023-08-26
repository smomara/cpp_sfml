#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Ball.h"

class Game
{
private:
	// Window
	sf::VideoMode videoMode;
	sf::RenderWindow* window;

	// Font variables
	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	// Game variables
	bool endGame;
	sf::Event sfmlEvent;

	// Player variables
	Player player;
	int points = 0;

	// Ball variables
	std::vector<Ball> balls;
	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;

	// Initialization Functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

public:
	// Constructors and Destructors
	Game();
	~Game();

	// Accessors
	const bool running() const;
	const bool& getEndgame() const;

	// Modifiers

	// Functions
	void pollEvents();

	void spawnBalls();
	const int randBallType() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();
};