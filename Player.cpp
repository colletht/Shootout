/*
Title: Cowboy Shootout!
Names: Harry Collet, Alexis Makowski, Parker Linhart-Wubbena
Labs: 1,13,5
Date: 4/23/18
Description: Code for a game where two cowboys face of in an EPIC showdown.
*/
#include "Player.h"

Player::Player(const sf::Vector2f & pos, sf::Vector2f & size, int difLevel, float gravity, float floorLevel, bool facingLeft, float iVelocity) :RectangleShape(size) {
	switch (difLevel)
	{
	case 1:
		this->bulletDelay = 30;	//approx 0.5 sec shoot delay
		this->blockDelay = 100;	//approx 2 sec block delay
		break;
	case 2:
		this->bulletDelay = 20;
		this->blockDelay = 70;
		break;
	case 3:
		this->bulletDelay = 10;
		this->blockDelay = 40;
		break;
	default:
		this->bulletDelay = 20;
		this->blockDelay = 45;
		break;
	}
	this->iVelocity = -iVelocity;
	this->setPosition(pos);
	this->gravity = gravity;
	this->ground = floorLevel;
	this->facingLeft = facingLeft;
}

void Player::jump()
{
	if (onGround && this->jumpDelay == 0) {
		this->yVelocity = this->iVelocity;
		this->onGround = false;
		this->jumpDelay = 30;
	}
}

bool Player::canShoot()
{
	return bulletTimer == 0;
}

Bullet & Player::shoot()
{
	this->bulletTimer = this->bulletDelay;
	if (this->facingLeft) {
		return *(new Bullet(*(new sf::Vector2f(this->getPosition().x - this->getSize().y*0.1, this->getPosition().y + this->getSize().y*0.5)), *(new sf::Vector2f(this->getSize().y*0.1, this->getSize().y*0.05)), this->facingLeft, 50));
	}
	else {
		return *(new Bullet(*(new sf::Vector2f(this->getPosition().x + this->getSize().x, this->getPosition().y + this->getSize().y*0.5)), *(new sf::Vector2f(this->getSize().y*0.1, this->getSize().y*0.05)), this->facingLeft, 50));
	}
}

void Player::block()
{
	if (this->blockTimer <= 0 && !this->blocking()) {
		if (this->facingLeft) {
			//makes blockZone on left side
			this->blockZone = sf::FloatRect(this->getPosition().x-this->getSize().x*0.5,this->getPosition().y, this->getSize().x*0.5,this->getSize().y);
		}
		else {
			//makes blockZone on right side
			this->blockZone = sf::FloatRect(this->getPosition().x + this->getSize().x, this->getPosition().y, this->getSize().x*0.5, this->getSize().y);
		}
	}
}

sf::FloatRect & Player::getBlockZone()
{
	return this->blockZone;
}

//if blockZone exists/is active
bool Player::blocking()
{
	return (sf::FloatRect(0,0,0,0) != this->blockZone);
}



void Player::executeActions()
{
	//deals with movement
	if (!this->onGround) {	//if the player is in the air, move it according to game physics
		this->move(0, yVelocity);
		yVelocity += gravity;
		if (this->getPosition().y + this->getSize().y >= this->ground) {
			this->onGround = true;
			this->setPosition(this->getPosition().x, ground - this->getSize().y);
		}
	}	
	if (this->jumpDelay != 0 && this->onGround) {
		this->jumpDelay--;
	}//finish handling gravity and movement of object, after this line coords of character should not change

	//handle block timer.
	if (this->blocking() || (this->blockTimer <= this->blockDelay && this->blockTimer != 0)) {
		if (this->blockTimer == 15) {	//cutoff for how long can block. at this point resets blockZone and awaits timer to be over
			this->blockZone = sf::FloatRect(0, 0, 0, 0);
		}
		if (this->blockTimer < 15) {	//if blockZone is still active then update its position so it is always in front of where the character is facing
			this->updateBlockZone();
		}
		if (this->blockTimer >= this->blockDelay) {
			this->blockTimer = 0;
		}
		else {
			++this->blockTimer;
		}
	}

	//bullets should be handled in main as they are their own entities and will have their own execute Actions funtion;
	//handle bullet delay here
	if (this->bulletTimer != 0) {
		this->bulletTimer--;
	}
}

bool Player::isDead()
{
	return this->dead;
}

void Player::died()
{
	this->dead = true;
}

//updates the position of the block so that it is always in front of the player
void Player::updateBlockZone()
{
	this->blockZone.top = this->getPosition().y;
}
