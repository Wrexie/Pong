
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
	float ballSpeedX, ballSpeedY;
	ballSpeedX = 7;
	ballSpeedY = 7;

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

	//Menu(s) text
	Event event;
	Text title("", font);
	Text start("", font);
	Text quit("", font);
	Text restart("", font);
	Text gameOver("", font);
	title.setString("Pong");
	start.setString("Start Game");
	quit.setString("Quit");
	restart.setString("Restart");
	gameOver.setString("Game Over!");
	title.setFillColor(Color::White);
	start.setFillColor(Color::White);
	quit.setFillColor(Color::White);
	restart.setFillColor(Color::White);
	gameOver.setFillColor(Color::White);
	title.setCharacterSize(50);
	start.setCharacterSize(45);
	quit.setCharacterSize(45);
	restart.setCharacterSize(45);
	gameOver.setCharacterSize(45);
	title.setStyle(Text::Bold | Text::Underlined);
	start.setStyle(Text::Bold);
	quit.setStyle(Text::Bold);
	restart.setStyle(Text::Bold);
	gameOver.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2, 100);
	start.setPosition(window.getSize().x / 2, 200);
	quit.setPosition(window.getSize().x / 2, 300);
	restart.setPosition(window.getSize().x / 2, 200);
	gameOver.setPosition(window.getSize().x / 2, 100);
	title.setOrigin(title.getLocalBounds().width / 2.0f, title.getLocalBounds().height / 2.0f);
	start.setOrigin(start.getLocalBounds().width / 2.0f, start.getLocalBounds().height / 2.0f);
	quit.setOrigin(quit.getLocalBounds().width / 2.0f, quit.getLocalBounds().height / 2.0f);
	restart.setOrigin(restart.getLocalBounds().width / 2.0f, restart.getLocalBounds().height / 2.0f);
	gameOver.setOrigin(gameOver.getLocalBounds().width / 2.0f, gameOver.getLocalBounds().height / 2.0f);
	quit.setOutlineColor(Color::Red);
	start.setOutlineColor(Color::Red);
	restart.setOutlineColor(Color::Red);
	start.setOutlineThickness(3);
	restart.setOutlineThickness(3);
	bool started = false;
	bool esc = false;
	bool over = false;
	int c = 0;

	//Main game loop
	bool isPlaying = false;
	while (window.isOpen()) {
		if (isPlaying) {
			while (window.pollEvent(event)) {
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Escape) {
						esc = true;
						isPlaying = false;
					}
				}
			}
			Vector2f ballPosition = ball.getPosition();
			Vector2f paddlePosition = paddleA.getPosition();
			ball.setPosition(ballPosition.x += ballSpeedX, ballPosition.y += ballSpeedY);

			if (ballPosition.y >= 590) {
				ballSpeedY *= -1;
			}
			else if (ballPosition.y <= 10) {
				ballSpeedY *= -1;
			}
			if (ballPosition.x >= 790) {
				ballSpeedX *= -1;
			}
			if (ballPosition.x <= (paddlePosition.x)) {
				ball.setPosition(400, 300);
				ballSpeedX *= -1;
				score = 0;
				text.setString(std::to_string(score));
				over = true;
				isPlaying = false;
			}
			else if (ballPosition.x <= paddlePosition.x + 10 && (ballPosition.y <= paddlePosition.y + 40 && ballPosition.y >= paddlePosition.y - 40)) {
				ballSpeedX *= -1;
				score++;
				text.setString(std::to_string(score));
			}
			if ((paddlePosition.y - 40) < 0) {
				paddleA.setPosition(paddlePosition.x, 40);
			}
			else if ((paddlePosition.y + 40) > 600) {
				paddleA.setPosition(paddlePosition.x, 560);
			}
			window.clear(Color::Black);
			window.draw(text);
			window.draw(ball);
			window.draw(paddleA);
			paddleA.handleKey();
			window.display();	
		}

		else if (!isPlaying) {
			if (esc == true) {
				while (window.pollEvent(event)) {
					if (event.type == Event::KeyPressed) {
						if (Keyboard::isKeyPressed(Keyboard::Escape)) {
							esc = false;
							isPlaying = true;
						}
						if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) {
							if (c == 0) {
								score = 0;
								text.setString(std::to_string(score));
								ball.setPosition(400, 300);
								ballSpeedX = 7;
								ballSpeedY = 7;
								paddleA.setPosition(20, 300);
								esc = false;
								isPlaying = true;
							}
							if (c == 1) {
								window.close();
							}
						}

						if (event.key.code == Keyboard::W) {
							if (c == 0) {
								c = 1;
								restart.setOutlineThickness(0);
								quit.setOutlineThickness(3);
								continue;
							}
							c -= 1;
							quit.setOutlineThickness(0);
							restart.setOutlineThickness(3);
							continue;
						}
						if (event.key.code == Keyboard::S) {
							if (c == 1) {
								c = 0;
								quit.setOutlineThickness(0);
								restart.setOutlineThickness(3);
								continue;
							}
							c += 1;
							restart.setOutlineThickness(0);
							quit.setOutlineThickness(3);
							continue;
						}
					}
					window.clear(Color::Black);
					window.draw(restart);
					window.draw(quit);
					window.display();
				}
			}
			if (started == false) {
				while (window.pollEvent(event)) {
					if (event.type == Event::KeyPressed) {
						if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) {
							if (c == 0) {
								started = true;
								isPlaying = true;
							}
							if (c == 1) {
								window.close();
							}
						}

						if (event.key.code == Keyboard::W) {
							if (c == 0) {
								c = 1;
								start.setOutlineThickness(0);
								quit.setOutlineThickness(3);
								continue;
							}
							c -= 1;
							quit.setOutlineThickness(0);
							start.setOutlineThickness(3);
							continue;
						}
						if (event.key.code == Keyboard::S) {
							if (c == 1) {
								c = 0;
								quit.setOutlineThickness(0);
								start.setOutlineThickness(3);
								continue;
							}
							c += 1;
							start.setOutlineThickness(0);
							quit.setOutlineThickness(3);
							continue;
						}
					}
					window.clear(Color::Black);
					window.draw(title);
					window.draw(start);
					window.draw(quit);
					window.display();
				}
			}
			if (over == true) {
				while (window.pollEvent(event)) {
					if (event.type == Event::KeyPressed) {
						if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) {
							if (c == 0) {
								ball.setPosition(400, 300);
								paddleA.setPosition(20, 300);
								over = false;
								isPlaying = true;
							}
							if (c == 1) {
								window.close();
							}
						}
						if (event.key.code == Keyboard::W) {
							if (c == 0) {
								c = 1;
								restart.setOutlineThickness(0);
								quit.setOutlineThickness(3);
								continue;
							}
							c -= 1;
							quit.setOutlineThickness(0);
							restart.setOutlineThickness(3);
							continue;
						}
						if (event.key.code == Keyboard::S) {
							if (c == 1) {
								c = 0;
								quit.setOutlineThickness(0);
								restart.setOutlineThickness(3);
								continue;
							}
							c += 1;
							restart.setOutlineThickness(0);
							quit.setOutlineThickness(3);
							continue;
						}
					}
				}
				window.clear(Color::Black);
				window.draw(restart);
				window.draw(quit);
				window.draw(gameOver);
				window.display();
			}
		}
	}
}

