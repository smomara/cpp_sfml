#include "Player.h"

// Initialization Functions
void Player::initVariables(float x, float y, float movementSpeed, int hpMax)
{
	this->shape.setPosition(x, y);
	this->movementSpeed = movementSpeed;
	this->hpMax = hpMax;
	this->hp = this->hpMax;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

// Constructors and Destructors
Player::Player(float x, float y, float movementSpeed, int hpMax)
{
	this->initVariables(x, y, movementSpeed, hpMax);
	this->initShape();
}

Player::~Player()
{
}

// Accessors
const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

// Functions
void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	// Window bounds collision

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
	this->updateInput();

	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
