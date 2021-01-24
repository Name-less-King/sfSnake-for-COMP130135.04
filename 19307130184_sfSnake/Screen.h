#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen
{
public:
	virtual void handleInput(sf::RenderWindow& window) = 0;//纯虚函数，必须在继承类中重新声明
	virtual void update(sf::Time delta) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

};

#endif