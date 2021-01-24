#include <SFML/Graphics.hpp>

#include <random>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 10.f;

Fruit::Fruit(sf::Vector2f position)
{	
	static std::default_random_engine engine(time(NULL));
	static std::uniform_int_distribution<int> ColorDistribution(0,7);

	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setOutlineColor(sf::Color::Magenta);
	shape_.setOutlineThickness(-1.f);

    switch (ColorDistribution(engine)) {
        case 0:
                shape_.setFillColor(sf::Color(128,64,64));//Color:Brown
                color_=sf::Color(128,64,64);
                break;
        case 1:
                shape_.setFillColor(sf::Color::Black);
                color_=sf::Color::Black;
                break;
        case 2:
                shape_.setFillColor(sf::Color::Red);
                color_=sf::Color::Red;
                break;
        case 3:
                shape_.setFillColor(sf::Color::Red);
                color_=sf::Color::Red;
                break;
        case 4:
                shape_.setFillColor(sf::Color::Blue);
                color_=sf::Color::Blue;
                break;
        case 5:
                shape_.setFillColor(sf::Color::Blue);
                color_=sf::Color::Blue;
                break;
        case 6:
                shape_.setFillColor(sf::Color::Green);
                color_=sf::Color::Green;
                break;
        case 7:
                shape_.setFillColor(sf::Color::Green);
                color_=sf::Color::Green;
                break;
    }
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Color Fruit::getFillColor() const
{
        return color_;
}