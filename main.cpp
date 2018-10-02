/*
Title: Cowboy Shootout!
Names: Harry Collet, Alexis Makowski, Parker Linhart-Wubbena
Labs: 1,13,5
Date: 4/23/18
Description: Code for a game where two cowboys face of in an EPIC showdown.
*/
#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "Menu.h"



int main() {
	
	sf::RenderWindow window(sf::VideoMode(1920, 1001), "Shootout");
	window.setFramerateLimit(60);
	
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())	{
		sf::Event event;
		while (window.pollEvent(event))	{
			switch (event.type)	{
			case sf::Event::KeyReleased:
				switch (event.key.code)	{
				case sf::Keyboard::Up:
				case sf::Keyboard::W:
				case sf::Keyboard::I:
					if (menu.getPage() != 2)
						menu.MoveUp();
					break;
				case sf::Keyboard::Down:
				case sf::Keyboard::S:
				case sf::Keyboard::K:
					if (menu.getPage() != 2)
						menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())	{
					case 0:
						if (menu.getPage() == 0) {
							menu.play(window);
						}
						else if (menu.getPage() == 1) {
							menu.setDifficulty();
							menu.setPage(0);
						}
						else if (menu.getPage() == 2)	{
							menu.setPage(0);
						}
						break;
					case 1:
						if (menu.getPage() == 0) {
							menu.setPage(1);
						}
						else if (menu.getPage() == 1)	{
							menu.setDifficulty();
							menu.setPage(0);
						}
						else if (menu.getPage() == 2)	{
							menu.setPage(0);
						}
						break;
					case 2:
						if (menu.getPage() == 0) {
							menu.setPage(2);
						}
						else if (menu.getPage() == 1)	{
							menu.setDifficulty();
							menu.setPage(0);
						}
						break;
					case 3:
						window.close();
						break;
					}
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		menu.draw(window);
		window.display();
	}
	return 0;
}