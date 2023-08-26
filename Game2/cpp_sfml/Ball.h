#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum BallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class Ball
{
private:
	// Shape
	sf::CircleShape shape;

	int type;

	// Initialization Functions
	void initShape(const sf::RenderWindow& window);

public:
	// Constructors and Destructors
	Ball(const sf::RenderWindow& window, int type);
	~Ball();

	// Accessors
	const sf::CircleShape& getShape() const;
	const int& getType() const;

	// Functions
	void update();
	void render(sf::RenderTarget* target);
};

