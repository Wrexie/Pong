#include <SFML/Graphics.hpp>

class Ball : public sf::RectangleShape
{
public:
	Ball(float xCoord, float yCoord)
		: sf::RectangleShape(sf::Vector2f{20, 20}), x{ xCoord }, y{ yCoord }{
		setFillColor(sf::Color::White);
		setPosition(x, y);
		setOrigin(10, 10);
		
	}

private:
	float x, y;
};

