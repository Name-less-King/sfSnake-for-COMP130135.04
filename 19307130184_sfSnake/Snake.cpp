#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(sf::Vector2f(0, -1)), hitSelf_(false) {
    initNodes();

    pickupBuffer_.loadFromFile("Sounds/pickup.wav");
    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);

    //dieBuffer_.loadFromFile("Sounds/die.wav");
    dieBuffer_.loadFromFile("Sounds/die_update.wav");
    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
}

void Snake::initNodes() {
    nodes_.push_back(
        SnakeNode(sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,
                               Game::Height / 2 - (SnakeNode::Height / 2)),
                  0));
    for (int i = 1; i < Snake::InitialSize; ++i) {
        nodes_.push_back(
            SnakeNode(sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,
                                   Game::Height / 2 - (SnakeNode::Height / 2) +
                                       (SnakeNode::Height * i))));
    }
}

//锁定方向，最多转角135度，防止自杀，符合正常游戏体验
void Snake::handleInput(sf::RenderWindow& window) {
    sf::Vector2f direction_next = direction_;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        direction_next = sf::Vector2f(0, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction_next = sf::Vector2f(0, 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        direction_next = sf::Vector2f(-1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction_next = sf::Vector2f(1, 0);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        SnakeNode& headNode = nodes_[0];
        float dx = sf::Mouse::getPosition(window).x - headNode.getPosition().x;
        float dy = sf::Mouse::getPosition(window).y - headNode.getPosition().y;
        float x_next = dx / sqrt(dx * dx + dy * dy);
        float y_next = dy / sqrt(dx * dx + dy * dy);
        direction_next = sf::Vector2f(x_next, y_next);
    }
    if (direction_.x * direction_next.x + direction_.y * direction_next.y >std::cos(5.0/4.0*3.141512))
        direction_ = direction_next;
}

void Snake::update(sf::Time delta) {
    move();
    checkEdgeCollisions();
    checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits) {
    decltype(fruits.begin()) toRemove = fruits.end();

    for (auto it = fruits.begin(); it != fruits.end(); ++it) {
        if (it->getBounds().intersects(nodes_[0].getBounds()))
            toRemove = it;
    }

    if (toRemove != fruits.end()) {
        pickupSound_.play();
        grow(*toRemove);
        fruits.erase(toRemove);
    }
}

void Snake::grow(sfSnake::Fruit& fruit) {
    auto color_ = fruit.getFillColor();
    auto grow_position =
        sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
                     nodes_[nodes_.size() - 1].getPosition().y);
    if (color_ == sf::Color(128, 64, 64) || color_ == sf::Color::Black)
        ;
    else if (color_ == sf::Color::Red) {
        for (auto i = 0; i < 3; ++i)
            nodes_.push_back(SnakeNode(grow_position));
    } else if (color_ == sf::Color::Blue) {
        for (auto i = 0; i < 2; ++i)
            nodes_.push_back(SnakeNode(grow_position));
    } else
        nodes_.push_back(SnakeNode(grow_position));
}

unsigned Snake::getSize() const {
    return nodes_.size();
}

bool Snake::hitSelf() const {
    return hitSelf_;
}

void Snake::checkSelfCollisions() {
    SnakeNode& headNode = nodes_[0];
	//以下借鉴了@杜雨轩同学的思路 不用边缘碰撞，而考虑圆心之间的距离是否在直径以下
    float head_x = headNode.getPosition().x;
    float head_y = headNode.getPosition().y;
    for (auto i = 1; i < nodes_.size(); ++i) {
        float dx = nodes_[i].getPosition().x - head_x;
        float dy = nodes_[i].getPosition().y - head_y;
        if (dx * dx + dy * dy <= 160) {
            dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            hitSelf_ = true;
        }
    }
}
void Snake::checkEdgeCollisions() {
    SnakeNode& headNode = nodes_[0];

    if (headNode.getPosition().x <= 0)
        headNode.setPosition(Game::Width-SnakeNode::Width/2, headNode.getPosition().y);
    else if (headNode.getPosition().x >= Game::Width)
        headNode.setPosition(SnakeNode::Width/2, headNode.getPosition().y);
    else if (headNode.getPosition().y <= 0)
        headNode.setPosition(headNode.getPosition().x, Game::Height-SnakeNode::Height/2);
    else if (headNode.getPosition().y >= Game::Height)
        headNode.setPosition(headNode.getPosition().x, SnakeNode::Height/2);
}

void Snake::move() {
    for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i) {
        nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
    }

    nodes_[0].move(direction_.x, direction_.y, 0);
    for (auto i = 1; i < nodes_.size(); ++i)
        nodes_[i].move(direction_.x, direction_.y);
}

void Snake::render(sf::RenderWindow& window) {
    for (auto node : nodes_)
        node.render(window);
}