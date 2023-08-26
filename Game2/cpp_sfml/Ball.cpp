#include "Ball.h"

// Initialization Functions
void Ball::initShape(const sf::RenderWindow& window)
{
	/*
		@return void

		Initialization Function

		Initialize the ball shape
		- random radius
		- color/outline depending on type
		- random position
	*/

	// Random size (10-20)
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	// Set Color
	sf::Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}
	this->shape.setFillColor(color);
	// Random position
	this->shape.setPosition(
		sf::Vector2f(
			static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->shape.getGlobalBounds().width)),
		    static_cast<float>(rand() % static_cast<int>(window.getSize().y - this->shape.getGlobalBounds().height))
		)
	);
}

// Constructors and Destructors
Ball::Ball(const sf::RenderWindow& window, int type)
	:type(type)
{
	/*
		Constructor

		Initializes a ball instance
	*/
	this->initShape(window);
}

Ball::~Ball()
{
	/*
		Destructor
	*/
}

const sf::CircleShape& Ball::getShape() const
{
	/*
		@return sf::CircleShape

		Accessor

		returns the ball's shape
	*/
	return this->shape;
}

const int& Ball::getType() const
{
	/*
		@return int

		Accessor

		returns the ball's type
	*/
	return this->type;
}

// Functions
void Ball::update()
{
	/*
		@return void

		Game Function
		- Update Function

		Main update function
	*/
}

void Ball::render(sf::RenderTarget* target)
{
	/*
		@return void

		Game Function
		- Render Function

		Main render function
		- renders the ball shape
	*/
	target->draw(this->shape);
}
