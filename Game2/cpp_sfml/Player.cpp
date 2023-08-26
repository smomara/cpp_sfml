#include "Player.h"

// Initialization Functions
void Player::initVariables(float x, float y, float movementSpeed, int hpMax)
{
	/*
		@return void

		Initialization Function

		Initializes necessary variables
	*/
	this->shape.setPosition(x, y);
	this->movementSpeed = movementSpeed;
	this->hpMax = hpMax;
	this->hp = this->hpMax;
}

void Player::initShape()
{
	/*
		@return void

		Initialization Function

		Initializes the player shape
	*/
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

// Constructors and Destructors
Player::Player(float x, float y, float movementSpeed, int hpMax)
{
	/*
		Constructor Function

		Initializes a player instance
		- calls all init functions
	*/
	this->initVariables(x, y, movementSpeed, hpMax);
	this->initShape();
}

Player::~Player()
{
	/*
		Destructor Function
	*/
}

// Accessors
const sf::RectangleShape& Player::getShape() const
{
	/*
		@return sf::RectangleShape

		Accessor Function

		Returns the shape of the player
	*/
	return this->shape;
}

const int& Player::getHp() const
{
	/*
		@return int

		Accessor Function

		Return the player's hp
	*/

	return this->hp;
}

const int& Player::getHpMax() const
{
	/*
		@return int

		Accessor Function

		Return the player's maximum possible hp
	*/

	return this->hpMax;
}

// Functions
void Player::takeDamage(const int damage)
{
	/*
		@return void

		Game Function

		Makes player take a certain amount of damage
		- remove hp if can take damage (more than 0)
		- ensure hp not negative
	*/
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	/*
		@return void

		Game Function

		Makes player gain a certain amount of health
		- add hp if can heal (less than max)
		- ensure hp not more than max
	*/
	if (this->hp < this->hpMax)
		this->hp += health;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	/*
		@return void

		Game Function
		- Update Function

		Updates the player's position based on keyboard input
		- left or right not both, then up or down not both
	*/

	// Keyboard input
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(sf::Vector2f(-this->movementSpeed, 0.f));
	}
	// Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(sf::Vector2f(this->movementSpeed, 0.f));
	}
	// Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(sf::Vector2f(0.f, -this->movementSpeed));
	}
	//Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(sf::Vector2f(0.f, this->movementSpeed));
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	/*
		@return void

		Game Function
		- Update Function

		Checks for player window collisions and updates accordingly
	*/
	sf::FloatRect playerBounds;
	//Left
	playerBounds = this->shape.getGlobalBounds();
	if (playerBounds.left <= 0.f)
		this->shape.setPosition(0.f, playerBounds.top);
	// Right
	else if (playerBounds.left + playerBounds.width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
	// Top
	playerBounds = this->shape.getGlobalBounds();
	if (playerBounds.top <= 0.f)
		this->shape.setPosition(playerBounds.left, 0.f);
	// Bottom
	else if (playerBounds.top + playerBounds.height >= target->getSize().y)
		this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
}

void Player::update(sf::RenderTarget* target)
{
	/*
		@return void

		Game Function
		- Update Function

		Main update function
		- calls all the update functions
	*/
	this->updateInput();

	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	/*
		@return void

		Game Function
		- Render Function

		Main render function
		- renders the player
	*/
	target->draw(this->shape);
}
