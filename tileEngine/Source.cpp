#include <iostream>
#include "Map.h"
#include "Camera.h"

int main() {
	Map map;
	
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "tileEngine", sf::Style::Default);
	sf::View camera = window.getDefaultView();
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		window.clear(sf::Color::Black);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) return 0;
			if (event.type == sf::Event::MouseWheelMoved) // Zomm in or out if the mouse wheel moves
			{
				camera.zoom(1.0f + event.mouseWheel.delta*0.01f);
			}
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					camera.move(0, -5);
					break;
				case sf::Keyboard::S:
					camera.move(0, 5);
					break;
				case sf::Keyboard::A:			
					camera.move(-5, 0);
					break;
				case sf::Keyboard::D:
					camera.move(5, 0);
					break;
				}
			}
		}
		map.drawMap(window);
		window.setView(camera);
		window.display();
	}

	return 0;
}