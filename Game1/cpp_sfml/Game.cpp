#include "Game.h"

void Game::initVariables()
{
	/*
		@return void

		- set window pointer to null pointer

		Initializes the variables
	*/

	this->window = nullptr;

	// Game logic
	this->endgame = false;
	this->points = 0;
	this->health = 100;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
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

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(0.5f, 0.5f);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/CONSOLA.TTF"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("POINTS");
	
	sf::FloatRect textRect = uiText.getLocalBounds();
	uiText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	uiText.setPosition(sf::Vector2f(this->window->getSize().x / 2.0f, 40.f));
}

void Game::initHealthbar()
{
	this->healthbarOutline.setSize(sf::Vector2f(500.f, 20.f));
	this->healthbarOutline.setFillColor(sf::Color(0, 0, 0, 0));
	this->healthbarOutline.setOutlineColor(sf::Color::White);
	this->healthbarOutline.setOutlineThickness(2.f);
	this->healthbarOutline.setPosition(150, 6);

	this->healthbarHealth.setSize(sf::Vector2f(500.f, 20.f));
	this->healthbarHealth.setFillColor(sf::Color::Red);
	this->healthbarHealth.setPosition(150, 6);
}

// Constructors + Destructors
Game::Game()
{
	/*
		Constructor
	*/

	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initHealthbar();
	this->initEnemies();
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

const bool Game::getEndgame() const
{
	/*
		@return bool

		Checks whether game ended
	*/
	
	return this->endgame;
}

// Functions
void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their color and position
		- sets a random position
		- sets a random color
		- adds enemy to the vector
	*/

	// set a random position
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	// set a color
	this->enemy.setFillColor(sf::Color::Green);

	// Add enemy to vector
	this->enemies.push_back(this->enemy);
}

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

void Game::updateMousePositions() {
	/*
		@return void

		Updates the mouse positions:
		- Mouse positions relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;

	ss << this->points;

	this->uiText.setString(ss.str());
	sf::FloatRect textRect = uiText.getLocalBounds();
	uiText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	uiText.setPosition(sf::Vector2f(this->window->getSize().x / 2.0f, 40));
}

void Game::updateEnemies()
{
	/*
		@return void

		Updates the enemy spawn time and spawns enemies when
		the total amount of enemies is less than the max
		Move the enemies downwards
		Removes the enemies at the edge of the screen or if clicked
	*/

	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	// Move and update the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(0.f, 3.f);

		// Check if bottom of screen
		if (this->enemies[i].getPosition().y >= this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);

			this->health -= 10;
		}

	}

	// Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					// Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					// Gain points
					this->points += 10;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateHealthbar()
{
	this->healthbarHealth.setSize(sf::Vector2f(
		this->health / 10 * 50,
		20.f
	));
}

void Game::update()
{
	/*
		@return void

		Updates the game objects:
		- poll events
		- update mouse position
		- update enemies
	*/

	this->pollEvents();

	if (this->endgame == false)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();

		this->updateHealthbar();
	}

	if (this->health <= 0)
		this->endgame = true;
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	// Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::renderHealthbar(sf::RenderTarget& target)
{
	target.draw(this->healthbarOutline);
	target.draw(this->healthbarHealth);
}

void Game::render()
{
	/*
		@return void

		- clear old frame
		- render objects
		----- render enemies
		- display frame in window

		Renders the game objects
	*/

	this->window->clear();

	// Draw Game Objects
	this->renderEnemies(*this->window);
	this->renderHealthbar(*this->window);
	this->renderText(*this->window);

	this->window->display();
}
