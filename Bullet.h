/*
Title: Cowboy Shootout!
Names: Harry Collet, Alexis Makowski, Parker Linhart-Wubbena
Labs: 1,13,5
Date: 4/23/18
Description: Code for a game where two cowboys face of in an EPIC showdown.
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

class Bullet :public sf::RectangleShape {
public:
	Bullet(sf::Vector2f & pos, sf::Vector2f & size, bool facingLeft, float iVelocity);
	~Bullet();

	void blocked();

	bool checkOutOfBounds(float x, float y);

	void executeActions();
private:
	bool facingLeft;
	float iVelocity;
};