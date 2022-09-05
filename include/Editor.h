#pragma once
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Grid.h"
#include "macros.h"

const int POP_UP_WINDOW_WIDTH = 550;
const int POP_UP_WINDOW_HEIGHT = 200;

class Editor
{
public:
	Editor();
	~Editor();
	void run();

private:
	void loadTextures();
	void copyFileToGrid();
	void popUpWindowInput();
	void handleClick(const sf::Event::MouseButtonEvent& ev);
	sf::Sprite createHoveredIcon() const;
	void drawHoveredIcon();
	void save();

	sf::RenderWindow m_window;
	std::vector<sf::Texture> m_textures; //hold only once in the program
	Menu m_menu;
	Grid m_grid;
	std::fstream m_file;
	sf::Vector2f m_mousePosition;

};