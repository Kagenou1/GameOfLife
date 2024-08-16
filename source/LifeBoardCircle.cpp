#include <LifeBoard.h>

LifeBoardCircle::LifeBoardCircle(const int &_field_width, const int &_field_height, const float &_cell_size)
    : LifeBoardRect(_field_width, _field_height, _cell_size)
{
}

void LifeBoardCircle::config_shape()
{
    cellShape = new sf::CircleShape(cell_size / 2 + cell_outline_thickness / 4);
}

sf::Vector2f LifeBoardCircle::get_cell_size() const
{
    return sf::Vector2f(cell_size + cell_outline_thickness * 2, cell_size + cell_outline_thickness * 2);
}

sf::Shape* LifeBoardCircle::clone() const
{
    return new sf::CircleShape(*(dynamic_cast<sf::CircleShape*>(cellShape)));
}
