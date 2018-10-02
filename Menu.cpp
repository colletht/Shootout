/*
Title: Cowboy Shootout!
Names: Harry Collet, Alexis Makowski, Parker Linhart-Wubbena
Labs: 1,13,5
Date: 4/23/18
Description: Code for a game where two cowboys face of in an EPIC showdown.
*/
#pragma once
#include "Menu.h"

//rules page back button
Menu::Menu(float width, float height)
{
	if (!this->font.loadFromFile("Fonts/Pixeled.ttf"))
	{
		std::cout << "could not load font" << std::endl;
	}
	if (!this->text.loadFromFile("images/cowboyo[1312].png")) {
		std::cout << "could not load image" << std::endl;
	}
	this->text.setRepeated(false);
	this->cowboy.setTexture(this->text);
	this->cowboy.setScale(2* 1920 / width, 2* 1001 / height);
	this->cowboy.setPosition(width*0.1, height*0.33);

	title.setFont(this->font);
	title.setColor(sf::Color::Red);
	title.setString("Shootout");
	title.setPosition(60,  60);
	title.setCharacterSize(width / 15);

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play Game");
	menu[0].setPosition(sf::Vector2f(width *0.66, height / (MAX_NUM_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Difficulty");
	menu[1].setPosition(sf::Vector2f(width *0.66, height / (MAX_NUM_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Rules");
	menu[2].setPosition(sf::Vector2f(width *0.66, height / (MAX_NUM_OF_ITEMS + 1) * 3));

	menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Exit Game");
	menu[3].setPosition(sf::Vector2f(width *0.66, height / (MAX_NUM_OF_ITEMS + 1) * 4));

	dif[0].setFont(font);
	dif[0].setColor(sf::Color::White);
	dif[0].setString("EASY");
	dif[0].setPosition(sf::Vector2f(width *0.66, height / (MAX_NUM_OF_ITEMS + 1) * 2));

	dif[1].setFont(font);
	dif[1].setColor(sf::Color::White);
	dif[1].setString("MEDIUM");
	dif[1].setPosition(sf::Vector2f(width *0.66, height / (MAX_NUM_OF_ITEMS + 1) * 3));

	dif[2].setFont(font);
	dif[2].setColor(sf::Color::White);
	dif[2].setString("HARD");
	dif[2].setPosition(sf::Vector2f(width *0.66, height / (MAX_NUM_OF_ITEMS + 1) * 4));

	this->difSpec.setFont(this->font);
	this->difSpec.setFillColor(sf::Color::White);
	this->difSpec.setString("Each difficulty decreases delay");
	this->difSpec.setPosition(width *0.5, height / (MAX_NUM_OF_ITEMS ));

	rule[0].setFont(font);
	rule[0].setColor(sf::Color::White);
	rule[0].setString("  This is a Two Player Game\n       Player 1-----Player 2\n           'A'       Block       'L'\n           'S'       Jump       'K'\n           'D'       Shoot      'J'\n\n                DON'T DIE!\n");
	rule[0].setPosition(sf::Vector2f(width *0.55, height / (MAX_NUM_OF_ITEMS + 1) * 1));

	rule[1].setFont(font);
	rule[1].setColor(sf::Color::Red);
	rule[1].setString("Main Menu");
	rule[1].setPosition(sf::Vector2f(rule[0].getGlobalBounds().left + rule[0].getGlobalBounds().width/2 - rule[1].getGlobalBounds().width/2, rule[0].getGlobalBounds().top + rule[0].getGlobalBounds().height + 5));

	SelectItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	if (page != 2) {
		for (int i = 0; i < MAX_NUM_OF_ITEMS; i++)
		{
			if (page == 0)
			{
				window.draw(menu[i]);
			}
			else if (page == 1)
			{
				window.draw(dif[i]);

			}
			else { cout << "problem" << endl; }
		}
	}
	else {
		for (int i = 0; i < 2; ++i) {
			window.draw(rule[i]);
		}
	}
	if (page == 1) {
		window.draw(this->difSpec);
	}
	window.draw(title);
	window.draw(this->cowboy);
}

void Menu::MoveUp()
{
	if (SelectItemIndex - 1 >= 0)
	{
		if (page == 0)
		{
			menu[SelectItemIndex].setColor(sf::Color::White);
			SelectItemIndex--;
			menu[SelectItemIndex].setColor(sf::Color::Red);
		}
		else if (page == 1)
		{
			dif[SelectItemIndex].setColor(sf::Color::White);
			SelectItemIndex--;
			dif[SelectItemIndex].setColor(sf::Color::Red);
		}
		else
		{
			rule[SelectItemIndex].setColor(sf::Color::White);
			SelectItemIndex--;
			rule[SelectItemIndex].setColor(sf::Color::Red);
		}

	}
}

void Menu::MoveDown()
{
	if (SelectItemIndex + 1 < MAX_NUM_OF_ITEMS)
	{
		if (page == 0)
		{
			menu[SelectItemIndex].setColor(sf::Color::White);
			SelectItemIndex++;
			menu[SelectItemIndex].setColor(sf::Color::Red);
		}
		else if (page == 1)
		{
			dif[SelectItemIndex].setColor(sf::Color::White);
			SelectItemIndex++;
			dif[SelectItemIndex].setColor(sf::Color::Red);
		}
		else
		{
			rule[SelectItemIndex].setColor(sf::Color::White);
			SelectItemIndex++;
			rule[SelectItemIndex].setColor(sf::Color::Red);
		}
	}
}

int Menu::GetPressedItem()
{
	return SelectItemIndex;
}

int Menu::play(sf::RenderWindow & window)
{
	//initialize bullet storage vector
	std::vector<Bullet> bullets;
	sf::Sprite Background;

	sf::Texture cowboy1, cowboy2, blockTexture, backgroundTexture;
	if (!cowboy1.loadFromFile("images/cowboyo[1312].png")) {
		std::cout << "inside if loop" << std::endl;
		return -1;
	}
	if (!cowboy2.loadFromFile("images/darkcowboyo[1311].png")) {
		std::cout << "inside if loop" << std::endl;
		return -1;
	}
	if (!blockTexture.loadFromFile("images/block.png")) {
		std::cout << "inside if loop" << std::endl;
		return -1;
	}
	if (!backgroundTexture.loadFromFile("images/cactusBackdrop.png")) {
		std::cout << "inside if loop" << std::endl;
		return -1;
	}
	else {
		Background.setTexture(backgroundTexture);
		Background.setScale(2.2, 1.6);
		Background.setTextureRect(sf::IntRect(0,0,window.getSize().x, window.getSize().y));
	}
	cowboy1.setRepeated(false);
	cowboy2.setRepeated(false);
	blockTexture.setRepeated(false);

	float ground = window.getSize().y*0.875;
	float gravity = window.getSize().y*0.008;
	sf::RectangleShape floor = sf::RectangleShape(*(new sf::Vector2f(window.getSize().x, window.getSize().y - ground)));
	floor.setPosition(*(new sf::Vector2f(0, ground)));
	floor.setFillColor(sf::Color(204, 145, 69));

	sf::Sprite tempBlockSprite;
	tempBlockSprite.setTexture(blockTexture);
	tempBlockSprite.setScale(0.5, 0.5);

	Player p1(*(new sf::Vector2f(0, ground)), *(new sf::Vector2f(window.getSize().x*0.2, window.getSize().y*0.4)), difficulty, gravity, ground, false, window.getSize().y*0.08);
	Player p2(*(new sf::Vector2f(window.getSize().x - window.getSize().x*0.2, ground)), *(new sf::Vector2f(window.getSize().x*0.2, window.getSize().y*0.4)), difficulty, gravity, ground, true, window.getSize().y*0.08);

	p1.setTexture(&cowboy1);
	p2.setTexture(&cowboy2);

	while (window.isOpen() && !p1.isDead() && !p2.isDead()) {	//while game is going on

		if (window.hasFocus()) {

			sf::Event event;

			while (window.pollEvent(event)) {

				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::S) {
						p1.jump();
					}
					if (event.key.code == sf::Keyboard::A) {
						p1.block();
					}
					if (event.key.code == sf::Keyboard::D && p1.canShoot()) {
						bullets.push_back(p1.shoot());
						bullets.back().setFillColor(sf::Color::Black);
					}
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::K) {
						p2.jump();
					}
					if (event.key.code == sf::Keyboard::L) {
						p2.block();
					}
					if (event.key.code == sf::Keyboard::J && p2.canShoot()) {
						bullets.push_back(p2.shoot());
						bullets.back().setFillColor(sf::Color::Black);
					}
				}
			}
			//execute actions of existing entities depending on previous inputs
			p1.executeActions();
			p2.executeActions();
			for (int i = 0; i < bullets.size(); ++i) {
				bullets.at(i).executeActions();
				if (bullets.at(i).checkOutOfBounds(window.getSize().x, window.getSize().y)) {
					bullets.erase(bullets.begin() + i);
				}
			}

			//after executing actions check for any collisions
			for (int i = 0; i < bullets.size(); ++i) {
				if (p1.blocking()) {
					if (bullets.at(i).getGlobalBounds().intersects(p1.getBlockZone())) {
						bullets.at(i).blocked();
					}
				}
				if (p2.blocking()) {
					if (bullets.at(i).getGlobalBounds().intersects(p2.getBlockZone())) {
						bullets.at(i).blocked();
					}
				}
				if (bullets.at(i).getGlobalBounds().intersects(p1.getGlobalBounds())) {
					p1.died();
				}
				if (bullets.at(i).getGlobalBounds().intersects(p2.getGlobalBounds())) {
					p2.died();
				}
			}

			window.clear();

			//draw background
			window.draw(Background);

			//drawing players
			window.draw(p1);
			if (p1.blocking()) {
				tempBlockSprite.setPosition(p1.getBlockZone().left, p1.getBlockZone().top);
				window.draw(tempBlockSprite);
			}
			window.draw(p2);
			if (p2.blocking()) {
				tempBlockSprite.setPosition(p2.getBlockZone().left, p2.getBlockZone().top);
				window.draw(tempBlockSprite);
			}

			//drawing bullets
			for (Bullet j : bullets) {
				window.draw(j);
			}
			window.draw(floor);
			window.display();
		}
	}
	bullets.clear();

	//prepping fonts for game over display
	sf::Text winDisplay, addInstructions;
	sf::Font pixeled;
	if (!pixeled.loadFromFile("Fonts/Pixeled.ttf")) {
		return -1;
	}
	winDisplay.setFont(pixeled);
	winDisplay.setFillColor(sf::Color::Red);
	winDisplay.setCharacterSize(window.getSize().y/13.34);
	addInstructions.setFont(pixeled);
	addInstructions.setFillColor(sf::Color::Red);
	addInstructions.setCharacterSize(winDisplay.getCharacterSize()*0.25);
	if (p1.isDead()) {
		winDisplay.setString("Player 2 Wins!");
	}
	else {
		winDisplay.setString("Player 1 Wins!");
	}
	addInstructions.setString("Press Space to Continue");

	winDisplay.setPosition(window.getSize().x / 2 - winDisplay.getGlobalBounds().width / 2, window.getSize().y / 2 - winDisplay.getGlobalBounds().height - 5);
	addInstructions.setPosition(window.getSize().x / 2 - addInstructions.getGlobalBounds().width / 2, window.getSize().y / 2 + 5);
	bool backToMenu = false;
	while (window.isOpen() && !backToMenu) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					backToMenu = true;
				}
			}
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();

		//draw background
		window.draw(Background);

		//drawing players
		window.draw(p1);
		if (p1.blocking()) {
			tempBlockSprite.setPosition(p1.getBlockZone().left, p1.getBlockZone().top);
			window.draw(tempBlockSprite);
		}
		window.draw(p2);
		if (p2.blocking()) {
			tempBlockSprite.setPosition(p2.getBlockZone().left, p2.getBlockZone().top);
			window.draw(tempBlockSprite);
		}

		window.draw(floor);
		window.draw(winDisplay);
		window.draw(addInstructions);
		window.display();
	}
	return 1;
}

void Menu::setPage(int newData)
{
	this->page = newData; if (newData == 2) {
		this->SelectItemIndex = 1; 
	}
	else { 
		this->SelectItemIndex = 0; 
	}
	if (page == 0)
	{
		for (int i = 0; i < MAX_NUM_OF_ITEMS; ++i) {
			if (i == this->SelectItemIndex)
				menu[SelectItemIndex].setColor(sf::Color::Red);
			else
				menu[i].setColor(sf::Color::White);
		}
	}
	else if (page == 1)
	{
		for (int i = 0; i < 3; ++i) {
			if (i == this->SelectItemIndex)
				dif[SelectItemIndex].setColor(sf::Color::Red);
			else
				dif[i].setColor(sf::Color::White);
		}
	}
	else
	{
		rule[SelectItemIndex].setColor(sf::Color::Red);
	}
}

int Menu::getPage()
{
	return this->page;
}

void Menu::setDifficulty()
{
	this->difficulty = this->SelectItemIndex;
}
