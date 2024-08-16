#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#include <LifeBoardBase.h>

class LifeBoardRect : public LifeBoardBase
{
public:
    LifeBoardRect(const int &_field_width, const int &_field_height, const float& _cell_size);

    int getCellAt(float x, float y) const override;

protected:

    sf::Vector2f get_position_from_index(const int& _index) const override;
    int getNeighboursCount(const states_array::const_iterator cell) override;
    sf::Vector2f get_cell_size() const override;
    void config_shape() override;

private: 

    sf::Shape* clone() const override;
};


class LifeBoardCircle : public LifeBoardRect
{
public:
    LifeBoardCircle(const int &_field_width, const int &_field_height, const float& _cell_size);
    
protected:

    sf::Vector2f get_cell_size() const override;
    void config_shape() override;

private: 

    sf::Shape* clone() const override;
};


class LifeBoardHexagon : public LifeBoardBase
{
public:
    LifeBoardHexagon(const int &_field_width, const int &_field_height, const float& _cell_size);

    int getCellAt(float x, float y) const override;

protected:

    sf::Vector2f get_position_from_index(const int& _index) const override;
    int getNeighboursCount(const states_array::const_iterator cell) override;
    sf::Vector2f get_cell_size() const override;
    void config_shape() override;    

private: 

    sf::Shape* clone() const override;
};

#endif// LIFEBOARD_H