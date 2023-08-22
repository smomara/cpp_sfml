#include "Game.h"

void Game::initVariables()
{
	/*
		@return void

		- set window pointer to null pointer

		Initializes the variables
	*/

	this->window = nullptr;
}

void Game::initWindow()
{
	/*
		@return void

		- initializes the window size
		- initializes the window

		Initializes the window
	*/

	// Initialize window size
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	// Initialize window
	this->window = new 	sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
}

// Constructors + Destructors
Game::Game()
{
	/*
		Constructor
	*/

	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	/*
		Destructor
	*/

	delete this->window;
}

// Accessors
const bool Game::running() const
{
	/*
		@return bool

		Checks whether the game is running
	*/

	return this->window->isOpen();
}

// Functions
void Game::pollEvents()
{
	/*
		@return void

		- loop while events are being polled
		- switch statement on event type
	
		Polls events
	*/

	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::update()
{
	/*
		@return void

		- poll events

		Updates the game objects
	*/

	this->pollEvents();
}

void Game::render()
{
	/*
		@return void

		- clear old frame
		- render objects
		- display frame in window

		Renders the game objects
	*/

	this->window->clear(sf::Color(0, 0, 255, 255));

	// Draw Game Objects

	this->window->display();
}