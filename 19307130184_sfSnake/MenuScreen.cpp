#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

#include "Game.h"
#include "GameScreen.h"
#include "MenuScreen.h"

using namespace sfSnake;

std::string bg_color[]={"Black","White","Brown"};
std::string grid_color[]={"White","Black","Brown","Close"};

MenuScreen::MenuScreen()
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit");

	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setColor(sf::Color::Green);
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 3);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        Game::bg_index = (Game::bg_index + 1) % 3;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        Game::grid_index = (Game::grid_index + 1) % 4;
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
	std::string text_now =(
        "\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit"
		"\n\nBefore playing:"
		"\n\nPress [Z] to switch \n\nbackground color to "+bg_color[Game::bg_index]+
		"\n\nPress [X] to switch \n\ngrid color to "+grid_color[Game::grid_index]);
    text_.setString(text_now);
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	window.draw(snakeText_);
}