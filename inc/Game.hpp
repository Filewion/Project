#include <SFML/Graphics.hpp>


#pragma once
class Game
{
public:
	Game();

	void Start();
	void MainEvent();
	void RestartGame();
	void SetWinner(short winner);
	short Winner();

private:
	unsigned short mode=0;
	sf::RenderWindow window;
	sf::Texture board_t, x_texture, o_texture;
	sf::Texture player_t, enemy_t;

	sf::Sprite board_sp;

	sf::Font arial;
	sf::Text game_status;
	sf::FloatRect gs_bounds;
	sf::RectangleShape square[4][4];
	sf::Event event;

	short matrix[4][4];
};