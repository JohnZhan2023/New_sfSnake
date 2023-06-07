#include "Grid.h"
#include <SFML/Graphics.hpp>

#include <memory>
#include<iostream>
#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;
Grid::Grid(int width, int height, int interval,sf::Color color){
    m_lines.setPrimitiveType(sf::Lines);
        for (int x = 0; x <= width; x += interval) {
            m_lines.append(sf::Vertex(sf::Vector2f(x, 0), color));
            m_lines.append(sf::Vertex(sf::Vector2f(x, height), color));
        }
        for (int y = 0; y <= height; y += interval) {
            m_lines.append(sf::Vertex(sf::Vector2f(0, y), color));
            m_lines.append(sf::Vertex(sf::Vector2f(width, y), color));
        }
}
