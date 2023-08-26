#include "Game.h"

// Initialization Functions
void Game::initVariables()
{
	/*
		@return void

		Initialize Function

		Initialize variables
	*/
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 10;
}

void Game::initWindow()
{
	/*
		@return void

		Initialize Function
	
		Initialize window
	*/
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	/*
		@return void

		Initialize Function
	
		Initialize fonts
	*/
	if (!this->font.loadFromFile("Fonts/CONSOLA.TTF"))
	{
		std::cout << "! ERROR::GAME::INITFONTS::COULD NOT LOAD CONSOLA.TTF" << std::endl;
	}
}

void Game::initText()
{
	/*
		@return void

		Initialize Function

		Initialize Text
		- guiText, endGameText
	*/

	// Initialize guiText
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(24);
	this->guiText.setString("guiText");

	// Initialize endGameText
	this->endGameText.setFont(this->font);
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(48);
	this->endGameText.setString("GAME OVER");

	// Center endGameText
	sf::FloatRect endGameTextRect = endGameText.getLocalBounds();
	endGameText.setOrigin(endGameTextRect.left + endGameTextRect.width / 2.f, endGameTextRect.top + endGameTextRect.height / 2.f);
	endGameText.setPosition(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}

// Constructors and Destructors
Game::Game()
{
	/*
		Constructor

		Initialize a Game instance
		- run all init functions
	*/
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	/*
		Destructor

		Delete the game instance
		- delete the window pointer
	*/
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	/*
		@return bool

		Accessor

		Returns whether or not the game is currently running
	*/
	return this->window->isOpen() /* && this->endGame == false*/;
}

const bool& Game::getEndgame() const
{
	/*
		@return bool

		Accessor

		Returns whether or not the game has ended
	*/
	return this->endGame;
}

// Functions
void Game::pollEvents()
{
	/*
		@ return void

		Game Function

		Polls Events
		- Check if closed by clicking close button or ESC
	*/
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnBalls()
{
	/*
		@return void

		Game Function

		Spawns in balls
	*/

	// Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->balls.size() < this->maxBalls)
		{
			this->balls.push_back(Ball(*this->window, this->randBallType()));
			this->spawnTimer = 0.f;
		}
	}
}

const int Game::randBallType() const
{
	/*
		@return int

		Game Function

		Returns a random ball type depending on how many points
	*/
	int type = BallTypes::DEFAULT;

	float otherProb = 15.f + this->points * 0.1f;

	if (otherProb > 30)
		otherProb = 30;

	int randValue = rand() % 100 + 1;
	
	if (randValue <= otherProb)
		type = BallTypes::HEALING;
	else if (randValue <= otherProb + otherProb)
		type = BallTypes::DAMAGING;
	
	return type;
}

void Game::updatePlayer()
{
	/*
		@return void

		Game Function
		- Update Function

		Updates the player and end the game if no hp
	*/
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::updateCollision()
{
	/*
		@return void

		Game Function
		- Update Function

		Checks for player collision with balls and updates according to type
		- default adds points
		- healing and damage add or subtract hp based on ball size
	*/

	// Check the collision
	for (size_t i = 0; i < this->balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			int ballSize = balls[i].getShape().getGlobalBounds().height;
			switch (this->balls[i].getType())
			{
			case BallTypes::DEFAULT:
				this->points++;
				break;
			case BallTypes::DAMAGING:
				this->player.takeDamage(ballSize);
				break;
			case BallTypes::HEALING:
				this->player.gainHealth(ballSize);
				break;
			}

			// Remove the ball from vector
			this->balls.erase(this->balls.begin() + i);
		}
	}
}

void Game::updateGui()
{
	/*
		@return void

		Game Function
		- Update Function

		Updates the GUI text with points and health
	*/
	std::stringstream ss;
	ss << " - Points: " << this->points << std::endl
		<< " - Health: " << this->player.getHp() << " / " << this->player.getHpMax() << std::endl;

	this->guiText.setString(ss.str());
}

void Game::update()
{
	/*
		@return void

		Game Function
		- Update Function

		Main update function
		- polls events
		- updates everything while the game hasn't ended
	*/

	// Poll Events
	this->pollEvents();

	if (this->endGame == false)
	{
		// Update Game
		this->spawnBalls();
		this->updatePlayer();
		this->updateCollision();

		// Update GUI
		this->updateGui();
	}
	
}

void Game::renderGui(sf::RenderTarget* target)
{
	/*
		@return void

		Game Function
		- Render Function

		Renders the GUI text
	*/
	target->draw(this->guiText);
}

void Game::render()
{
	/*
		@return void

		Game Function
		- Render Function

		Main render function
		- clears the old window frame
		- renders all balls, renders the player, render GUI text
		- renders end game text if game ended
		- displays the new window frame
	*/

	// Clear the old frame
	this->window->clear();

	// Render game
	for (auto i : this->balls)
	{
		i.render(this->window);
	}
	this->player.render(this->window);

	// Render GUI
	this->renderGui(this->window);

	// Render End Game
	if (this->endGame)
		this->window->draw(this->endGameText);

	// Display the new frame
	this->window->display();
}
