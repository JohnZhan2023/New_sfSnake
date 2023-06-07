#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0),int fruitColor=0);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	int fruitType;
	sf::Vector2f returnPos()const;

	
private:
	sf::CircleShape shape_;
	sf::Vector2f position_;
	static const float Radius;
};
}

#endif