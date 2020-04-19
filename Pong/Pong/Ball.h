#include <SFML/Graphics.hpp>

class Ball : public sf::CircleShape
{
public:
	Ball(float xCoord, float yCoord)
		: sf::CircleShape(5), x{ xCoord }, y{ yCoord }{
		setFillColor(sf::Color::White);
		setPosition(x, y);
	}

private:
	float x, y;
};

