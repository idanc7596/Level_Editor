#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "Button.h"
#include "macros.h"

//constants used for drawing grid:
const int GRID_HEIGHT = WINDOW_HEIGHT 
                        - (WINDOW_WIDTH - 2 * MARGIN_SIZE)/NUM_OF_ICONS //MENU_HEIGHT
                        - 3 * MARGIN_SIZE,
          GRID_WIDTH = WINDOW_WIDTH - 2 * MARGIN_SIZE;

class Grid : public sf::Drawable
{
public:
	Grid();
	void init(int rows, int cols);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void reset();
	void setTile(int row, int col, int type, const sf::Texture * texture);
	sf::Vector2f getTileSize() const;
	bool isFilledTile(const sf::Vector2f& mousePosition) const;
	bool wasClicked(const sf::Vector2f& clickPosition);
	void handleClick(const Button* currClickedButton, const sf::Vector2f& clickPosition,
					 int currClickedButtonType, const sf::Texture* currClickedButtonTexture);
	int getNumOfRows() const;
	int getNumOfCols() const;

	int getTileType(int row, int col) const;


private:
	void eraseCurrentFigure(int currClickedButtonType);
	
	int m_rows;
	int m_cols;
	std::vector<std::vector<Tile>> m_grid;
	sf::Vector2f m_position; 
	Tile* m_currClickedTile; 
};