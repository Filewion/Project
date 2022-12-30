#include <iostream>
#include "Game.hpp"

using namespace sf; // создание меню 
Game::Game()
{
    if (!board_t.loadFromFile("txtrs/Cells.png"))
        std::cout << "Error";
    if (!x_texture.loadFromFile("txtrs/X.png"))
        std::cout << "Error";
    if (!o_texture.loadFromFile("txtrs/O.png"))
        std::cout << "Error";
    if (!arial.loadFromFile("fnts/fonty.ttf"))
        std::cout << "Error";

    board_sp.setTexture(board_t); // текстура игрового оля 
    board_sp.setPosition(95, 75); // размещение 
    player_t = x_texture;
    enemy_t = o_texture;
}
void Game::Start()
{
    window.create(VideoMode(800, 800), "Tic Tac Toe"); // окно игры
    window.setFramerateLimit(30); // ограничение по FPS

    for (unsigned short i = 1, xp = 0; i <= 3; i++, xp += 140)
    {
        for (unsigned short j = 1, sp = 0; j <= 3; j++, sp += 120)
        {
            square[i][j].setSize({ 170,170 });
            square[i][j].setPosition(95 * j + sp, 75 * i + xp);
            matrix[i][j] = -1;
        }
    }
    while (window.isOpen())
    {
        MainEvent();

        window.clear(Color::White);
        window.draw(board_sp);

        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                window.draw(square[i][j]);
        window.display();
    }

}


short Game::Winner() // проверка на победу 
{
    unsigned short sum_player, sum_enemy;

    for (unsigned short i = 1; i <= 3; i++) // по строкам 
    {
        sum_enemy = sum_player = 0;

        for (unsigned short j = 1; j <= 3; j++)
        {
            if (matrix[i][j] == 1)
                sum_player++;

            if (matrix[i][j] == 0)
                sum_enemy++;
        }
        if (sum_player == 3)
            return 0;
        if (sum_enemy == 3)
            return 1;
    }
    sum_enemy = sum_player = 0;

    for (unsigned short i = 1; i <= 3; i++) // по столбцам 
    {
        sum_enemy = sum_player = 0;

        for (unsigned short j = 1; j <= 3; j++)
        {
            if (matrix[j][i] == 1)
                sum_player++;

            if (matrix[j][i] == 0)
                sum_enemy++;
        }
        if (sum_player == 3)
            return 0;
        if (sum_enemy == 3)
            return 1;
    }
    sum_enemy = sum_player = 0;

    for (unsigned short i = 1; i <= 3; i++) // по одной диагонали 
    {

        if (matrix[i][i] == 1)
            sum_player++;
        if (matrix[i][i] == 0)
            sum_enemy++;

        if (sum_player == 3)
            return 0;
        if (sum_enemy == 3)
            return 1;

    }

    sum_enemy = sum_player = 0;

    for (unsigned short i = 1; i <= 3; i++) // по другой 
    {

        if (matrix[i][4 - i] == 1)
            sum_player++;
        if (matrix[i][4 - i] == 0)
            sum_enemy++;

        if (sum_player == 3)
            return 0;
        if (sum_enemy == 3)
            return 1;
    }

    for (unsigned short i = 1; i <= 3; i++) 
    {
        for (unsigned short j = 1; j <= 3; j++)
        {
            if (matrix[i][j] == -1)
                return -1;
        }
    }
    return 2;
}


void Game::RestartGame()
{
    for (unsigned short i = 1; i <= 3; i++)
    {
        for (unsigned short j = 1; j <= 3; j++)
        {
            matrix[i][j] = -1;
            square[i][j].setTexture(NULL);
        }
    }
    return;
}

void Game::SetWinner(short winner)
{
    if (winner == -1)
        return;
    /*if (winner == 0)
        game_status = Text("qqqqq", arial, 40);
    if (winner == 1)
        game_status = Text("qqqqqq", arial, 40);
    if (winner == 2)
        game_status = Text("qqqqqq", arial, 40);
    game_status.setFillColor(Color::Black);
    game_status.setPosition(150, 150);
    window.draw(game_status);*/
    RestartGame();
    return;
}

void Game::MainEvent()
{
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
        {
            window.close();
            break;
        }
        case Event::KeyPressed:
        {
            if (event.key.code == Keyboard::R)
            {
                RestartGame();
            }
            break;
        }
        case Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                for (unsigned short i = 1; i <= 3; i++)
                {
                    for (unsigned short j = 1; j <= 3; j++)
                    {
                        if (square[i][j].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) // проверка на соответствие координат мыши и поля
                        {
                            if (matrix[i][j] == -1)
                            {
                                if (mode % 2 == 0)
                                {
                                    matrix[i][j] = 0;
                                    square[i][j].setTexture(&player_t);
                                }
                                else
                                {
                                    matrix[i][j] = 1;
                                    square[i][j].setTexture(&enemy_t);
                                }
                                mode++;
                                SetWinner(Winner());
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }
        default:
            break;
        }
    }
}