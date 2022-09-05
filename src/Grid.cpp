#include "Grid.h"
#include <iostream>

Grid::Grid()
	: m_rows(0), m_cols(0),
	  m_position(sf::Vector2f(MARGIN_SIZE,
		2 * MARGIN_SIZE + (WINDOW_WIDTH - 2 * MARGIN_SIZE) / NUM_OF_ICONS)),
	  m_currClickedTile(nullptr)
{
}

//builds empty grid with the given dimensions:
void Grid::init(int rows, int cols)
{
	//for second initializations after clear button pressed:
	m_grid.clear(); 
	m_position = sf::Vector2f(MARGIN_SIZE,
		2 * MARGIN_SIZE + (WINDOW_WIDTH - 2 * MARGIN_SIZE) / NUM_OF_ICONS);
	m_currClickedTile = nullptr;
	m_rows = rows;
	m_cols = cols;

	//no input file case:
	float tileEdge = std::min(GRID_HEIGHT / float(m_rows),
		GRID_WIDTH / float(m_cols));
	sf::Vector2f tileSize(tileEdge, tileEdge);

	//for centering:
	m_position.x += (GRID_WIDTH - m_cols * tileEdge) / 2.f;

	//creates the two-dimensional vector of Tiles:
	sf::Vector2f currTilePos(m_position);
	for (int i = 0; i < m_rows; i++) {
		std::vector<Tile> row;
		for (int j = 0; j < m_cols; j++) {
			Tile tile(tileSize, currTilePos);
			currTilePos.x += tileEdge;
			row.push_back(tile);
		}
		currTilePos.x = m_position.x;
		currTilePos.y += tileEdge;
		m_grid.push_back(row);
	}

}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			target.draw(m_grid[i][j]);
		}
	}
}

//make all tiles empty:
void Grid::reset()
{
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			m_grid[i][j].reset();
		}
	}
}

//set the tile int (row,col) coordinates to a specific type 
//with the appropriate texture:
void Grid::setTile(int row, int col, int type, const sf::Texture* texture)
{
	if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) {
		m_grid[row][col].setType(type);
		m_grid[row][col].setTexture(texture);
	}
}

//return the size of the tile's edge in the grid:
sf::Vector2f Grid::getTileSize() const
{
	if (!m_grid.empty() && !m_grid[0].empty()) {
		return m_grid[0][0].getSize();
	}

	return sf::Vector2f(0, 0);
}

//return if the tile in the given position is filled (without texture):
bool Grid::isFilledTile(const sf::Vector2f& mousePosition) const
{
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (m_grid[i][j].createShape().getGlobalBounds().contains(mousePosition)) {
				return m_grid[i][j].isFilled();
			}
		}
	}

	return false;
}

//checks if any tile in the grid was clicked:
bool Grid::wasClicked(const sf::Vector2f& clickPosition)
{
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (m_grid[i][j].createShape().getGlobalBounds().contains(clickPosition)) {
				m_currClickedTile = &m_grid[i][j];
				return true;
			}
		}
	}

	return false;
}

//parameters: current clicked button in menu, mouse click position, 
//type and texture of current clicked button
void Grid::handleClick(const Button* currClickedButton, const sf::Vector2f& clickPosition,
					   int currClickedButtonType, const sf::Texture* currClickedButtonTexture)
{
	
	if (currClickedButton == nullptr || 
		currClickedButton->getType() == CLEAR ||
		currClickedButton->getType() == SAVE ||
		(currClickedButton->getType() != ERASE && isFilledTile(clickPosition)) ) {
		return;
	}
	if (currClickedButton->getType() == ERASE && isFilledTile(clickPosition) ) {
		m_currClickedTile->reset(); 
		return;
	} 

	if (currClickedButton->getType() == KING || currClickedButton->getType() == MAGE ||
		currClickedButton->getType() == WARRIOR || currClickedButton->getType() == THIEF) {
		eraseCurrentFigure(currClickedButtonType); //make sure only one figure drawn
		m_currClickedTile->setType(currClickedButtonType);
		m_currClickedTile->setTexture(currClickedButtonTexture);
	}

	else if (currClickedButton->getType() == WALL || currClickedButton->getType() == GATE ||
			currClickedButton->getType() == FIRE || currClickedButton->getType() == ORC ||
			currClickedButton->getType() == KEY || currClickedButton->getType() == TELEPORT ||
			currClickedButton->getType() == THRONE) {
		m_currClickedTile->setType(currClickedButtonType);
		m_currClickedTile->setTexture(currClickedButtonTexture);
	}
}

int Grid::getNumOfRows() const
{
	return m_rows;
}

int Grid::getNumOfCols() const
{
	return m_cols;
}

int Grid::getTileType(int row, int col) const
{
	return m_grid[row][col].getType();
}

void Grid::eraseCurrentFigure(int currClickedButtonType)
{
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (m_grid[i][j].getType() == currClickedButtonType)
				m_grid[i][j].reset();
		}
	}
}
