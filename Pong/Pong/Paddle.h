#include <SFML/Graphics.hpp>

class Paddle : public sf::RectangleShape {
public:
	Paddle(float xCoord) 
		: sf::RectangleShape(sf::Vector2f{ 10, 50 }), x{ xCoord }{
		setFillColor(sf::Color::White);
		setPosition(x, 0);
	}
	void setKeys(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) {
		kUp = upKey;
		kDown = downKey;
	}
	bool handleKey() {
		if (sf::Keyboard::isKeyPressed(kUp)) {
			move(up);
		}
		else if (sf::Keyboard::isKeyPressed(kDown)) {
			move(down);				
		}
		else {
			return false;
		}
		return true;
	}

private:
	float x;
	sf::Keyboard::Key kUp, kDown;
	static const sf::Vector2f up, down;
};
const sf::Vector2f Paddle::up{ 0, -0.1f };
const sf::Vector2f Paddle::down{ 0, +0.1f };

