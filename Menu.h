/*
Title: Cowboy Shootout!
Names: Harry Collet, Alexis Makowski, Parker Linhart-Wubbena
Labs: 1,13,5
Date: 4/23/18
Description: Code for a game where two cowboys face of in an EPIC showdown.
*/#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Player.h"
using namespace std;
#define MAX_NUM_OF_ITEMS 4

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	//int main_menu();
	int play(sf::RenderWindow & window);
	void setPage(int newData);
	int getPage();
	void setDifficulty();
private:
	int SelectItemIndex;
	sf::Font font;
	sf::Text title;
	sf::Text menu[MAX_NUM_OF_ITEMS];
	sf::Text dif[4];
	sf::Text difSpec;
	sf::Text rule[2];
	sf::Texture text;
	sf::Sprite cowboy;
	int page = 0; //from 0-2 3 pages total
	int difficulty;
};