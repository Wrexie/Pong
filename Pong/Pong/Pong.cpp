
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

	//Start menu
	Event event;
	Text title("", font);
	Text start("", font);
	Text quit("", font);
	Text restart("", font);
	title.setString("Pong");
	start.setString("Start Game");
	quit.setString("Quit");
	restart.setString("Restart");
	title.setFillColor(Color::White);
	start.setFillColor(Color::White);
	quit.setFillColor(Color::White);
	restart.setFillColor(Color::White);
	title.setCharacterSize(50);
	start.setCharacterSize(45);
	quit.setCharacterSize(45);
	restart.setCharacterSize(45);
	title.setStyle(Text::Bold | Text::Underlined);
	start.setStyle(Text::Bold);
	quit.setStyle(Text::Bold);
	restart.setStyle(Text::Bold);
	title.setPosition(window.getSize().x / 2, 100);
	start.setPosition(window.getSize().x / 2, 200);
	quit.setPosition(window.getSize().x / 2, 300);
	restart.setPosition(window.getSize().x / 2, 200);
	title.setOrigin(title.getLocalBounds().width / 2.0f, title.getLocalBounds().height / 2.0f);
	start.setOrigin(start.getLocalBounds().width / 2.0f, start.getLocalBounds().height / 2.0f);
	quit.setOrigin(quit.getLocalBounds().width / 2.0f, quit.getLocalBounds().height / 2.0f);
	restart.setOrigin(restart.getLocalBounds().width / 2.0f, restart.getLocalBounds().height / 2.0f);
	quit.setOutlineColor(Color::Red);
	start.setOutlineColor(Color::Red);
	restart.setOutlineColor(Color::Red);
	start.setOutlineThickness(3);
	restart.setOutlineThickness(3);
	bool esc = false;
	int c = 0;

	//Main game loop
	bool isPlaying = false;
	while (window.isOpen()) {
		if (isPlaying) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == Keyboard::Escape) {
						if (esc == false) {
							esc = true;
							continue;
						}
						if (esc == true) {
							esc = false;
							continue;
						}

					}
				}
			}
			if (esc == true) {
				while (window.pollEvent(event)) {
					if (event.type == Event::KeyPressed) {
						if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) {
							if (c == 0) {
								score = 0;
								text.setString(std::to_string(score));
								ball.setPosition(400, 300);
								paddleA.setPosition(10, 300);
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
						else if (event.key.code == Keyboard::S) {
							if (c == 1) {
								c == 0;
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
				window.display();
			}

			if (esc == false) {
				Vector2f bPos = ball.getPosition();
				Vector2f pPos = paddleA.getPosition();
				ball.setPosition(bPos.x += dx, bPos.y += dy);


				if (bPos.y >= 590) {
					dy *= -1;
				}
				else if (bPos.y <= 10) {
					dy *= -1;
				}
				if (bPos.x >= 790) {
					dx *= -1;
				}
				if (bPos.x <= (pPos.x)) {
					ball.setPosition(400, 300);
					dx *= -1;
					score = 0;
					text.setString(std::to_string(score));
				}
				else if (bPos.x <= pPos.x + 10 && (bPos.y <= pPos.y + 40 && bPos.y >= pPos.y - 40)) {
					dx *= -1;
					score++;
					text.setString(std::to_string(score));
				}

				if ((pPos.y - 40) < 0) {
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

		else if (!isPlaying) {
			while (window.pollEvent(event)) {
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) {
						if (c == 0) {
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
					else if (event.key.code == Keyboard::S) {
						if (c == 1) {
							c == 0;
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
			}

			window.clear(Color::Black);
			window.draw(title);
			window.draw(start);
			window.draw(quit);
			window.display();
		}
	}
}

