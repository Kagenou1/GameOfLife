#include <LifeBoard.h>

LifeBoardRect::LifeBoardRect(const int &_field_width, const int &_field_height, const float &_cell_size)
    : LifeBoardBase(_field_width, _field_height, _cell_size)
{
    boardShape.setSize(sf::Vector2f(field_width * (cell_size + cell_outline_thickness * 2) + field_outline_thickness * 2, field_height * (cell_size + cell_outline_thickness * 2) + field_outline_thickness * 2));
    field_size = field_height * field_width;
}

int LifeBoardRect::getCellAt(float x, float y) const
{
    int col = static_cast<int>((x - field_outline_thickness) / get_cell_size().x);
    int row = static_cast<int>((y - field_outline_thickness) / get_cell_size().y);

    if (col >= 0 && col < field_width && row >= 0 && row < field_height) 
    {
        return row * field_width + col;
    } 
    else 
    {
        return -1; // Нажатие вне поля
    }
}

sf::Vector2f LifeBoardRect::get_position_from_index(const int &_index) const
{
    return sf::Vector2f(_index % field_width * (cell_size + cell_outline_thickness * 2) + field_outline_thickness, _index / field_width * (cell_size + cell_outline_thickness * 2) + field_outline_thickness);
}

int LifeBoardRect::getNeighboursCount(const states_array::const_iterator cell)
{
    int neighbours_count = -1;
    if(true)
    {
        neighbours_count = 0;
        int temp_index = (*cell).first;
        if (temp_index % field_width != 0)
        {
            if(cells_states.contains(temp_index - field_width - 1))
                neighbours_count += cells_states.at(temp_index - field_width - 1);

            if(cells_states.contains(temp_index + field_width - 1))
                neighbours_count += cells_states.at(temp_index + field_width - 1);

            if(cells_states.contains(temp_index - 1))
                neighbours_count += cells_states.at(temp_index - 1);
        }
        if ((temp_index + 1) % field_width != 0)
        {
            if(cells_states.contains(temp_index - field_width + 1))
                neighbours_count += cells_states.at(temp_index - field_width + 1);

            if(cells_states.contains(temp_index + 1))
                neighbours_count += cells_states.at(temp_index + 1);
                
            if(cells_states.contains(temp_index + field_width + 1))
                neighbours_count += cells_states.at(temp_index + field_width + 1);

        }
                
        if(cells_states.contains(temp_index - field_width))
            neighbours_count += cells_states.at(temp_index - field_width);
  
        if(cells_states.contains(temp_index + field_width))
            neighbours_count += cells_states.at(temp_index + field_width);
    }
    
    return neighbours_count;
}

sf::Vector2f LifeBoardRect::get_cell_size() const
{
    return dynamic_cast<sf::RectangleShape*>(cellShape)->getSize();
}

void LifeBoardRect::config_shape()
{
    cellShape = new sf::RectangleShape(sf::Vector2f(cell_size + cell_outline_thickness * 2, cell_size + cell_outline_thickness * 2));
}

sf::Shape *LifeBoardRect::clone() const
{
    return new sf::RectangleShape(*(dynamic_cast<sf::RectangleShape*>(cellShape)));
}
