
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

using namespace sf;

int main()
{
	//Video Mode Object
	VideoMode vm(800, 600);

	//Render the window
	RenderWindow window(vm, "Pong - By: Wrexie", Style::Default);

	//Paddle
	//Paddle paddleA = Paddle(390);

	//Ball
	Ball ball = Ball(400, 300);

	//Main game loop
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		window.clear(Color::Black);
		window.draw(ball);

		window.display();
	}
}

