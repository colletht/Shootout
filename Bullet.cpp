/*
Title: Cowboy Shootout!
Names: Harry Collet, Alexis Makowski, Parker Linhart-Wubbena 
Labs: 1,13,5
Date: 4/23/18
Description: Code for a game where two cowboys face of in an EPIC showdown. 
*/
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f & pos, sf::Vector2f & size, bool facingLeft, float iVelocity) :RectangleShape(size) {
	this->setPosition(pos);
	this->facingLeft = facingLeft;
	if (this->facingLeft) {
		this->iVelocity = -iVelocity;
	}
	else {
		this->iVelocity = iVelocity;
	}
}

Bullet::~Bullet() {}

void Bullet::blocked()
{
	this->iVelocity = -this->iVelocity;
}

bool Bullet::checkOutOfBounds(float x, float y)
{
	if (this->getPosition().x < 0 || this->getPosition().x > x || this->getPosition().y < 0 || this->getPosition().y > y) {
		return true;
	}
	return false;
}

void Bullet::executeActions() {
	this->move(iVelocity, 0);
}