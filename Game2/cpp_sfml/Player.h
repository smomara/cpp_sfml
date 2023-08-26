#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	// Shape
	sf::RectangleShape shape;

	// Variables
	float movementSpeed;
	int hp;
	int hpMax;

	// Initialization functions
	void initVariables(float x, float y, float movementSpeed, int hpMax);
	void initShape();

public:
	// Constructors and Destructors
	Player(float x = 0.f, float y = 0.f, float movementSpeed = 5.f, int hpMax = 100);
	~Player();

	// Accessors
	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	// Functions
	void takeDamage(const int damage);
	void gainHealth(const int health);

	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(sf::RenderTarget* target);

	void render(sf::RenderTarget* target);
};

