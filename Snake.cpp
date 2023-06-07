#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(0.0f,1.0f), hitSelf_(false)
//这里direction必须要有一个初始值，我开始设置为（0，0），由于后面节点往前挤就会误以为碰撞到自己
{
	initNodes();
	autoSwitch=0;
	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{	nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - SnakeNode::Height / 2),1));
	for (int i = 1; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) - (SnakeNode::Height *i)),0));
	}
	
}

void Snake::handleInput(sf::RenderWindow& window)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{direction_.x = 0.0f;direction_.y = -1.0f;}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{direction_.x = 0.0f;direction_.y = 1.0f;}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{direction_.x = -1.0f;direction_.y = 0.0f;}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{direction_.x = 1.0f;direction_.y = 0.0f;}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{	sf::Vector2i m_position = sf::Mouse::getPosition(window);
		sf::Vector2f m_positionf(m_position.x,m_position.y);
		sf::Vector2f direction = m_positionf - nodes_[0].getPosition();
		float len = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x = direction.x / len;
		direction.y = direction.y / len;

		direction_ = direction;
		
	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		grow(toRemove->fruitType);
		fruits.erase(toRemove);
	}
}

void Snake::grow(int fruitType)
{	for(int i=1;i<=fruitType;++i){
	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
			nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
//当转变为鼠标控制后，由于行进轨迹不再横平竖直，所以节点间方块会在转动时挤压到
{
	SnakeNode& headNode = nodes_[0];
	
	for (decltype(nodes_.size()) i = 4; i < nodes_.size(); ++i)
	//这里由于蛇头在旋转时会压到第二个节点，所以不可以对第二个节点进行判断
	{	
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
		
	}

}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		nodes_[i].followDirection(nodes_[i-1]);
		//这里蛇的节点在斜着走的时候不可横平竖直
	}
		nodes_[0].setDirection(direction_.x , direction_.y);
		nodes_[0].move(10*direction_.x,10*direction_.y);
		
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto node : nodes_)
		node.render(window);
}

void Snake::autogo(sf::Vector2f direction_auto){
	double angle = acos(direction_auto.x * direction_.x + direction_auto.y * direction_.y);
	sf::Vector2f direction_tempo;
	if(angle< 3.1415*120/180){
		direction_tempo=direction_;
		direction_=direction_auto;
	}
	SnakeNode imagery= nodes_[0];
	imagery.move(20*direction_.x,20*direction_.y);
	int flag=0;
	for (decltype(nodes_.size()) i = 4; i < nodes_.size(); ++i)
	{	
		if (imagery.getBounds().intersects(nodes_[i].getBounds()))
		{
			flag=1;
		}
		
	}
	if(flag)
		direction_=direction_tempo;
}

sf::Vector2f Snake::returnPosition()const{
	return nodes_[0].returnPos();
}