#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable
{
public:
    Grid(int width, int height, int interval,sf::Color color);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_lines, states);
    }

//需要定义父类的virtual函数来便于具体target在绘制时调用？？
    sf::VertexArray m_lines;
};
