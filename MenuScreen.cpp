#include <SFML/Graphics.hpp>

#include <memory>
#include<iostream>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "Grid.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play,then[A] autoplay"
		"\n\nPress [ESC] to quit"
		"\n\n[G]to change grid"
		"\n\n[C]to change background");
	text_.setCharacterSize(20);
	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setFillColor(sf::Color::Green);
	//这里setColor已经过时，应该使用setFillColor
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
	text_.setFillColor(sf::Color::Green);
	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);

	//初始化colors
	colors.push_back(sf::Color::White);
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color(139, 69, 19) );
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		Game::backgroundColor+=1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		Game::gridColor+=1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{	window.clear(colors[Game::backgroundColor%3]);
	window.draw(Grid(Game::Width,Game::Height,20,colors[Game::gridColor%3]));
	window.draw(text_);
	window.draw(snakeText_);
	
}