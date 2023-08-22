#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Game class
	Acts as the game engine
	Wrapper class
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Game logic
	bool endgame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	
	sf::RectangleShape healthbarOutline;
	sf::RectangleShape healthbarHealth;

	// Private functions
	void initVariables();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();
	void initHealthbar();

public:
	// Constructors + Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;
	const bool getEndgame() const;

	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateHealthbar();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderHealthbar(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

#endif
