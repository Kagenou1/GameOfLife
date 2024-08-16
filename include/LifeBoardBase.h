#ifndef LIFEBOARDBASE_H
#define LIFEBOARDBASE_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <concepts>
#include <iostream>

template <class T>
concept is_sfml_shape = std::is_base_of_v<sf::Shape, T>;

enum Board_Type
{
    Rectangle_Type = 0,
    Circle_Type = 1,
    Hexagon_Type = 2
};

class LifeBoardBase : public sf::Drawable, public sf::Transformable
{

public:
    LifeBoardBase(const int &_field_width, const int &_field_height, const float& _cell_size);

    virtual void init();
    virtual void doCycle();

    virtual int getCellAt(float x, float y) const = 0;
    virtual bool markCell(const int &cell_index, bool changeBack = false);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual ~LifeBoardBase();

protected:
    typedef std::unordered_map<int,bool> states_array;
    typedef std::vector<sf::Shape*> cells_array;

    virtual void config_shape() = 0;
    virtual sf::Vector2f get_position_from_index(const int& _index) const = 0;

    virtual sf::Vector2f get_cell_size() const = 0;
    sf::Shape* cellShape = nullptr;

    float cell_size;
    float cell_outline_thickness = 0.5;
    sf::Color cell_outline_color = sf::Color(255,69,0);
    sf::Color cell_default_color = sf::Color::Transparent;
    sf::Color cell_marked_color = sf::Color::White;

    virtual int getNeighboursCount(const states_array::const_iterator cell) = 0;

    sf::RectangleShape boardShape;

    float field_outline_thickness = 2;
    sf::Color field_outline_color = sf::Color(255,127,80);
    sf::Color field_fill_color = sf::Color::Transparent;
    int field_width, field_height;

    cells_array field;
    states_array cells_states;

    int field_size;
private:

    virtual sf::Shape* clone() const = 0;
};

#endif// LIFEBOARDBASE_H