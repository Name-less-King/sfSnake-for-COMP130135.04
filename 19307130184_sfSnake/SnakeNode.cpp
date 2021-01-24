#include <SFML/Graphics.hpp>

#include<cmath>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 20.f;
const float SnakeNode::Height = 20.f;
sf::Texture texture1;
sf::Texture texture2;

SnakeNode::SnakeNode(sf::Vector2f position,int flag)
: position_(position)
{	if(flag==0){
	texture1.loadFromFile("Pic/head.png");
	shape_.setOrigin(sf::Vector2f(10.f, 10.f));
	shape_.setTexture(texture1);
	shape_.setPosition(position_);
	}
	else{
	texture2.loadFromFile("Pic/body.png");
	shape_.setOrigin(sf::Vector2f(10.f, 10.f));
	shape_.setTexture(texture2);
	shape_.setPosition(position_);
	}
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

void SnakeNode::move(float xOffset, float yOffset,int flag)
{	if (flag==0){
	position_.x += xOffset*SnakeNode::Width;
	position_.y += yOffset*SnakeNode::Height;
	shape_.setPosition(position_);
	}
	//此处借鉴了@杜雨轩同学的思路，使得贪吃蛇转向后的图形更加自然 
	if(fabs(xOffset)<1e-6){
        if(yOffset>0)shape_.setRotation(180.f);
		else if(yOffset<0)shape_.setRotation(-180.f);
    }
    else if(fabs(yOffset)<1e-6){
        if(xOffset>0)shape_.setRotation(90.f);
        else if(xOffset<0)shape_.setRotation(-90.f);
    }
    else{
        if(xOffset<0&&yOffset<0)
		shape_.setRotation(-std::atan((float)(xOffset/yOffset))/3.14*180);
        else if(xOffset>0&&yOffset<0)
		shape_.setRotation(std::atan((float)(-xOffset/yOffset))/3.14*180);
        else if(xOffset<0&&yOffset>0)
		shape_.setRotation(-180.f+std::atan((float)(-xOffset/yOffset))/3.14*180);
        else if(xOffset>0&&yOffset>0)
		shape_.setRotation(180.f-std::atan((float)(xOffset/yOffset))/3.14*180);  
}
}
sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}