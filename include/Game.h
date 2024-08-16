#ifndef GAME_H
#define GAME_H

#include <LifeBoard.h>
#include <thread>
#include <chrono>

class GameOfLife
{
public:

    GameOfLife();

    void setPosition(const float& _coord_x, const float& _coord_y);

    void init(const int& field_type, const int& _field_width, const int& _field_height, const float& _cell_size = 10);

    
    LifeBoardBase* getBoard() const {return board;};

private:

    LifeBoardBase* board = nullptr;
};

#endif// GAME_H
