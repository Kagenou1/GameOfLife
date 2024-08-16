#include <iostream>
#include <Game.h>
#include <filesystem>
#include "wtypes.h"

namespace fs = std::filesystem;
constexpr int ZOOM_SENSITIVITY = 4;
constexpr float GAME_POSITION_X = 25;
constexpr float GAME_POSITION_Y = 75;


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    float field_width = 100, field_height = 100, cell_size = 10;
    int cell_type = 0;
    std::cout << "Input field width >> ";
    std::cin >> field_width;
    std::cout << "Input field height >> ";
    std::cin >> field_height;
    do
    {   
        std::cout << "Input cell type (rectangle = 0, circle = 1, hexagon = 2) >> ";
        std::cin >> cell_type;
    }
    while(cell_type < 0 && cell_type > 2);
    // Создаем объект игры
	GameOfLife game;

    game.init(cell_type, field_width, field_height, cell_size);
	game.setPosition(GAME_POSITION_X, GAME_POSITION_Y);

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Game Of Life", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("C:/Users/vasilyev.an/source/repos/GameOfLife/resources/calibri.ttf");

	// Текст с обозначением клавиш
	sf::Text text("F2 - New Game / Esc - Exit", font, 20);
    sf::Text text2("", font, 20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(5.f, 5.f);
    text2.setPosition(5.f, 25.f);

	sf::Event event;

    std::atomic<bool> active = false, focused = true, lastEventHere = false, keyHold = false;

    sf::View game_view = window.getView();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
            lastEventHere.store(true);
			if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::LostFocus)
                focused.store(false);
            if (event.type == sf::Event::GainedFocus)
                focused.store(true);
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
				// Новая игра
				if (event.key.code == sf::Keyboard::F2)
				{
					game.init(cell_type, field_width, field_height, cell_size);
                    game.setPosition(GAME_POSITION_X, GAME_POSITION_Y);
                    text2.setString("");
				}
                if(event.key.code == sf::Keyboard::Space)
                {
                    if(active == false)
                    {
                        text2.setString("ACTIVE");
                        active = true;
                    }
                    else
                    {
                        text2.setString("PAUSED");
                        active = false;
                    }
                }
			}
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    keyHold.store(true);
                    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    game.getBoard()->markCell(game.getBoard()->getCellAt(worldPos.x - GAME_POSITION_X, worldPos.y - GAME_POSITION_Y), true);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    keyHold.store(false);
                }
            }
            if(event.type == sf::Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta > 0)
                {
                    game_view.zoom(0.9);
                    //std::cout << "Zoom in" << std::endl;
                }
                else
                {
                    game_view.zoom(1.1);
                    //std::cout << "Zoom out" << std::endl;
                }
                sf::Vector2f old_center = game_view.getCenter();
                //std::cout << std::format("Old center - ({},{})", old_center.x, old_center.y) << std::endl;
                //std::cout << std::format("Mouse pos - ({},{})", event.mouseWheel.x, event.mouseWheel.y) << std::endl;
                sf::Vector2f new_center(old_center.x + (event.mouseWheel.x - old_center.x) / ZOOM_SENSITIVITY, old_center.y + (event.mouseWheel.y - old_center.y) / ZOOM_SENSITIVITY);
                game_view.setCenter(new_center);
                window.setView(game_view);
            }

            if(keyHold.load())
            {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                game.getBoard()->markCell(game.getBoard()->getCellAt(worldPos.x - GAME_POSITION_X, worldPos.y - GAME_POSITION_Y));
            }

		}

        if(active.load() && focused.load())
        {
            game.getBoard()->doCycle();
        }

        if (active.load() && focused.load() || lastEventHere.load())
        {
            window.clear();
            window.draw(*game.getBoard());
            window.draw(text);
            window.draw(text2);
            window.display();
        }
        lastEventHere.store(false);
        
	}
    return 0;
}