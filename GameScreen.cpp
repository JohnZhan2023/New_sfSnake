#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include<iostream>
#include<cmath>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "Grid.h"
#include "Fruit.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
//初始化colors
	generateFruit();
	colors.push_back(sf::Color::White);
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color(139, 69, 19) );
}

void GameScreen::handleInput(sf::RenderWindow& window)
{	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		snake_.autoSwitch=!snake_.autoSwitch;
	if(snake_.autoSwitch==0)
		snake_.handleInput(window);
	else if(snake_.autoSwitch==1)
		snake_.autogo(shortestway());
}

void GameScreen::update(sf::Time delta)
{	
	if (fruit_.size() <= 4)
		generateFruit();


	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{	
	window.clear(colors[Game::backgroundColor%3]);
	window.draw(Grid(Game::Width,Game::Height,20,colors[Game::gridColor%3]));
	snake_.render(window);
	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);
	std::uniform_int_distribution<int> range(0, 7);
	
	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),range(engine)));
	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),range(engine)));
	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),range(engine)));
	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),range(engine)));
	
}

sf::Vector2f GameScreen::shortestway(){
	sf::Vector2f direction_2{0.0f,0.0f};
	double distance{10000};
	for(Fruit fruit: fruit_){
		sf::Vector2f snakepos{snake_.returnPosition()};
		if(((fruit.returnPos().x-snakepos.x)*(fruit.returnPos().x-snakepos.x)+(fruit.returnPos().y-snakepos.y)*(fruit.returnPos().y-snakepos.y))<(distance*distance))
			{	
				distance=sqrt(((fruit.returnPos().x-snakepos.x)*(fruit.returnPos().x-snakepos.x)+(fruit.returnPos().y-snakepos.y)*(fruit.returnPos().y-snakepos.y)));
				direction_2=sf::Vector2f((-snakepos.x+fruit.returnPos().x)/distance,(-snakepos.y+fruit.returnPos().y)/distance);	
			}
	}
	return direction_2;
}

