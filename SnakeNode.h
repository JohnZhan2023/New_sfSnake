#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{

	class SnakeNode
	{
	public:
		SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), int character_tempo = 0);

		void setPosition(sf::Vector2f position);
		void setPosition(float x, float y);

		void move(float xOffset, float yOffset);

		void render(sf::RenderWindow &window);

		sf::Vector2f getPosition() const;
		sf::FloatRect getBounds() const;

		void setDirection(double x_, double y_);
		void followDirection(SnakeNode &node);

		static const float Width;
		static const float Height;
		sf::Vector2f returnPos()const;
		//遵循封装的原则

	private:
		sf::Sprite shape_;
		sf::Vector2f position_;

		int character;
	};
}

#endif