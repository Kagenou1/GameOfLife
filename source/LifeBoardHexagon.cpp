#include <LifeBoard.h>

LifeBoardHexagon::LifeBoardHexagon(const int &_field_width, const int &_field_height, const float &_cell_size)
    : LifeBoardBase(_field_width, _field_height, _cell_size)
{
    boardShape.setSize(sf::Vector2f((field_width + 1) * (cell_size + cell_outline_thickness * 4) + field_outline_thickness * 2, field_height * (cell_size + cell_outline_thickness * 4) + field_outline_thickness * 2));
    field_size = field_height * field_width;
}

int LifeBoardHexagon::getCellAt(float x, float y) const
{
    return 0;
}

sf::Vector2f LifeBoardHexagon::get_position_from_index(const int &_index) const
{
    return sf::Vector2f((_index % field_width + float((_index / field_width) % 2) / 2) * (cell_size + cell_outline_thickness * 4) + field_outline_thickness, _index / field_width * (cell_size + cell_outline_thickness * 4) + field_outline_thickness);
}

int LifeBoardHexagon::getNeighboursCount(const states_array::const_iterator cell)
{
    return 0;
}

sf::Vector2f LifeBoardHexagon::get_cell_size() const
{
    return sf::Vector2f();
}

void LifeBoardHexagon::config_shape()
{
    cellShape = new sf::CircleShape(cell_size / 2 + cell_outline_thickness * 4, 6);
}

sf::Shape *LifeBoardHexagon::clone() const
{
    return new sf::CircleShape(*(dynamic_cast<sf::CircleShape*>(cellShape)));
}
