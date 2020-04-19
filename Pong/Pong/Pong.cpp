
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

	//Main game loop
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
	}
}

