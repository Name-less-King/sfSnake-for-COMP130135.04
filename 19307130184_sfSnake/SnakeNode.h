#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include<vector>

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0),int flag = 1);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset,int flag=1);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	static const float Width;
	static const float Height;

private:
	sf::Sprite shape_;
	sf::Vector2f position_;
};
}

#endif