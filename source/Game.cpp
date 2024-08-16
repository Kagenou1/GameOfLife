#include <Game.h>

GameOfLife::GameOfLife() 
{
    board = nullptr;
}

void GameOfLife::setPosition(const float &_coord_x, const float &_coord_y)
{
    board->setPosition(_coord_x, _coord_y);
}

void GameOfLife::init(const int& field_type, const int &_field_width, const int &_field_height, const float &_cell_size)
{
    if(board != nullptr)
    {
        delete board;
        board = nullptr;
    }

    switch (field_type)
    {
    case Rectangle_Type:
        board = new LifeBoardRect(_field_width, _field_height, _cell_size);
        break;
    case Circle_Type:
        board = new LifeBoardCircle(_field_width, _field_height, _cell_size);
        break;
    case Hexagon_Type:
        board = new LifeBoardHexagon(_field_width, _field_height, _cell_size);
        break;
    default:
        break;
    }
    if(board != nullptr)
        board->init();
    else
        std::cerr << "Initialization error" << std::endl;
}