#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

sf::Color bg_color[3]={sf::Color::Black,sf::Color::White,
sf::Color(128,64,64)};
sf::Color grid_color[4]={sf::Color::White,sf::Color::Black,
sf::Color(128,64,64),sf::Color::Transparent};

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() <= 5)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	bg_render(window);
	grid_render(window);
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
	
}
	
	

void GameScreen::generateFruit()
{	
	static std::default_random_engine engine(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width  - SnakeNode::Width );
    static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}

void bg_render(sf::RenderWindow& window){	
    sf::RectangleShape shape_;
    shape_.setPosition(sf::Vector2f(0, 0));
    shape_.setFillColor(bg_color[Game::bg_index]);
    shape_.setSize(sf::Vector2f(Game::Width, Game::Height));
    window.draw(shape_);
}

void grid_render(sf::RenderWindow& window){
	for (int y = SnakeNode::Height; y < Game::Height;y += SnakeNode::Height) {
        sf::RectangleShape shape_row;
        shape_row.setPosition(sf::Vector2f(0, y));
        shape_row.setFillColor(grid_color[Game::grid_index]);
        shape_row.setSize(sf::Vector2f(Game::Width, -1.0f));
        window.draw(shape_row);
    }
	for (int x = SnakeNode::Width; x < Game::Width;x += SnakeNode::Width) {
        sf::RectangleShape shape_col;
        shape_col.setPosition(sf::Vector2f(x, 0));
        shape_col.setFillColor(grid_color[Game::grid_index]);
        shape_col.setSize(sf::Vector2f(-1.0f, Game::Height));
        window.draw(shape_col);
}}
