#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 10.f;
const float SnakeNode::Height = 10.f;

		 sf::Texture texture1;
		 sf::Texture texture2;

SnakeNode::SnakeNode(sf::Vector2f position, int character_tempo)
	: position_(position)
{
	character = character_tempo;
	if (character == 1)
	{
		texture1.loadFromFile("Texture/image5.png");

		shape_.setTexture(texture1);
		shape_.setPosition(position_);
		shape_.setScale(0.2f, 0.2f);
	}
	else if (character == 0)
	{

		texture2.loadFromFile("Texture/image3.png");
		shape_.setTexture(texture2);
		shape_.setPosition(position_);
		shape_.setScale(0.2f, 0.2f);
	}
	
	sf::FloatRect shapeBounds = shape_.getLocalBounds();
	shape_.setOrigin(shapeBounds.left + shapeBounds.width / 2, shapeBounds.top + shapeBounds.height / 2);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow &window)
{

	window.draw(shape_);
}

void SnakeNode::setDirection(double x_, double y_)
{
	float angle;
	if (y_ > 0)
		angle = acos(x_) * 180 / 3.1416;
	// 前面direction_已经归一化过了，所以这里实际上是y_/1
	else
		angle = -acos(x_) * 180 / 3.1416;
	shape_.setRotation(angle + 90);

}

void SnakeNode::followDirection(SnakeNode &node)
{
	float angle = node.shape_.getRotation();
	shape_.setRotation(angle);
}

sf::Vector2f SnakeNode::returnPos()const{
	return position_;
}