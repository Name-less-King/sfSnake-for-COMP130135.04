#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	static const int Width = 1600;
	static const int Height = 900;
	
	static int bg_index;
	static int grid_index;
	//增加两组静态变量，通过在menuscreen和gamescreen之间共用来达到控制背景颜色和网格颜色的目的
	//一定要共用的原因是考虑到玩家的游戏体验，在游戏进行中更改背景颜色和网格颜色显然不太科学，必须在menu中设置好

	static std::shared_ptr<Screen> Screen;

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	
	static const sf::Time TimePerFrame;
};
}


#endif