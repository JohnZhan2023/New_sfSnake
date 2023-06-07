#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include <iostream>

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position,int fruitColor)
{	position_=position;
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	
	switch(fruitColor){
	case 0 : shape_.setFillColor(sf::Color(20, 20, 20) );fruitType=0;break;
	case 1 : shape_.setFillColor(sf::Color(139, 69, 19) );fruitType=0;break;
	case 2 :
	case 3 : shape_.setFillColor(sf::Color::Red );fruitType=1;break;
	case 4 :
	case 5 : shape_.setFillColor(sf::Color::Blue );fruitType=2;break;
	case 6 :
	case 7 : shape_.setFillColor(sf::Color::Green );fruitType=3;break;

	}
	shape_.setOutlineThickness(2); 
	shape_.setOutlineColor(sf::Color::White); 
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f Fruit::returnPos()const{
	return position_;
}