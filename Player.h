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
#include "Bullet.h"

class Player :public sf::RectangleShape {
public:
	Player(const sf::Vector2f & pos, sf::Vector2f & size, int difLevel, float gravity, float floorLevel, bool facingLeft, float iVelocity);

	void jump();

	bool canShoot();

	Bullet & shoot();

	void block();

	sf::FloatRect & getBlockZone();

	bool blocking();

	void executeActions();

	bool isDead();

	void died();
private:
	void updateBlockZone();

	bool facingLeft = true;
	bool onGround = false;
	bool dead = false;
	int jumpDelay = 0;
	int bulletTimer = 0;
	int bulletDelay;
	int blockTimer = 0;
	int blockDelay;	//has categories, counts until a set number to time how long block is active, then the rest is how long until block can become active again
	float yVelocity = 0;
	float iVelocity = 0;
	int ground;
	float gravity;
	sf::FloatRect blockZone;
};