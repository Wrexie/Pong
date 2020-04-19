
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
	window.setFramerateLimit(30);

	//Paddle
	Paddle paddleA = Paddle(20);
	paddleA.setKeys(Keyboard::Key::W, Keyboard::Key::S);

	//Ball
	Ball ball = Ball(400, 300);
	float dx, dy;
	dx = 7;
	dy = 7;

	//Score
	int score = 0;
	Font font;
	font.loadFromFile("slkscr.ttf");
	Text text("", font);
	text.setString(std::to_string(score));
	text.setFillColor(Color::White);
	text.setCharacterSize(30);
	text.setStyle(Text::Bold);
	text.setPosition(750, 10);

	//Main game loop
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		Vector2f bPos = ball.getPosition();
		Vector2f pPos = paddleA.getPosition();
		ball.setPosition(bPos.x += dx, bPos.y += dy);
		
		if (bPos.y >= 590) {
			dy *= -1;
		}
		else if(bPos.y <= 10) {
			dy *= -1;
		}
		if (bPos.x >= 790) {
			dx *= -1;
		}
		else if (bPos.x <= 10) {
			ball.setPosition(400, 300);
			dx *= -1;
			score = 0;
			text.setString(std::to_string(score));
		}
		else if (bPos.x <= pPos.x + 10 && bPos.x >= pPos.x && (bPos.y <= pPos.y + 40 && bPos.y >= pPos.y - 40)) {
			dx *= -1;
			score++;
			text.setString(std::to_string(score));
		}

		if((pPos.y - 40) < 0) {
			paddleA.setPosition(pPos.x, 40);
		}
		else if ((pPos.y + 40) > 600) {
			paddleA.setPosition(pPos.x, 560);
		}

		window.clear(Color::Black);
		window.draw(text);
		window.draw(ball);
		window.draw(paddleA);
		paddleA.handleKey();


		window.display();
	}
}

