#include <LifeBoardBase.h>

LifeBoardBase::LifeBoardBase(const int &_field_width, const int &_field_height, const float& _cell_size) 
    : field_width(_field_width), field_height(_field_height), cell_size(_cell_size)
{
    boardShape.setOutlineThickness(field_outline_thickness);
	boardShape.setOutlineColor(field_outline_color);
    boardShape.setFillColor(field_fill_color);
}

void LifeBoardBase::init()
{
    config_shape();

    cellShape->setFillColor(cell_default_color);
    cellShape->setOutlineColor(cell_outline_color);
    cellShape->setOutlineThickness(cell_outline_thickness);

    for (unsigned int i = 0; i < field_size; i++)
	{
        auto position = get_position_from_index(i);
        cellShape->setPosition(position);
        field.push_back(clone());
        cells_states.insert({i, false});
    }
}

void LifeBoardBase::doCycle()
{
    states_array new_states;
    for(auto iter = cells_states.cbegin(); iter != cells_states.cend(); iter++)
    {
        int neighbours_count = getNeighboursCount(iter);

        std::pair cell((*iter).first, (*iter).second);
        switch (neighbours_count)
        {
        case 2:
            break;
        case 3:
            cell.second = true;
            break;        
        default:
            cell.second = false;
            break;
        }
        new_states.insert(cell);

        sf::Color new_color;
        if(cell.second)
        {
            new_color = cell_marked_color;
        }
        else
        {
            new_color = cell_default_color;
        }
        field[cell.first]->setFillColor(new_color);
    }
    cells_states = new_states;
}

void LifeBoardBase::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

    target.draw(boardShape, states);

    for (const auto cell : field)
	{
        target.draw(*cell, states);
	}
}

LifeBoardBase::~LifeBoardBase()
{
    if(cellShape != nullptr)
    {
        delete cellShape;
        cellShape = nullptr;
    }
    for(auto ptr : field)
    {
        delete ptr;
    }
}

bool LifeBoardBase::markCell(const int &cell_index, bool changeBack)
{
    if(cell_index < 0 || cell_index >= field_size)
        return false;
    bool state = cells_states.at(cell_index);
    if(changeBack)
    {
        sf::Color new_color;
        if (state)
        {
            new_color = cell_default_color;
        }        
        else
        {
            new_color = cell_marked_color;
        }
        field.at(cell_index)->setFillColor(new_color);
        cells_states.at(cell_index) = !state;
        return true;
    }
    else
    {
        if(state)
            return false;
        else
        {
            field.at(cell_index)->setFillColor(cell_marked_color);
            cells_states.at(cell_index) = true;
            return true;
        }
    }
}
