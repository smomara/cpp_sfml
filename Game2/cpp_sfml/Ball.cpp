#include "Ball.h"

// Initialization Functions
void Ball::initShape(const sf::RenderWindow& window)
{
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
	this->initShape(window);
}

Ball::~Ball()
{

}

const sf::CircleShape& Ball::getShape() const
{
	return this->shape;
}

const int& Ball::getType() const
{
	return this->type;
}

// Functions
void Ball::update()
{
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
