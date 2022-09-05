#include "Tile.h"


Tile::Tile(sf::Vector2f size, sf::Vector2f position, int type, sf::Texture* texture)
	:m_size(size), m_position(position), m_type(type), m_texture(texture)
{
}

//create rectangle shape for the tile with the texture 
sf::RectangleShape Tile::createShape() const
{
	sf::RectangleShape rec(m_size);
	rec.setOutlineThickness(1.f);
	rec.setOutlineColor(sf::Color::Black);
	rec.setPosition(m_position);
	if (m_texture) { //textured tile
		rec.setTexture(m_texture);
	}
	else { //empty tile
		rec.setFillColor(sf::Color::White);
	}

	return rec;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->createShape());
}

//make the tile empty
void Tile::reset() 
{
	m_type = EMPTY;
	m_texture = nullptr;
}

void Tile::setTexture(const sf::Texture *texture)
{
	m_texture = texture;
}

const sf::Texture* Tile::getTexture() const
{
	return m_texture;
}

void Tile::setType(int type)
{
	m_type = type;
}

int Tile::getType() const
{
	return m_type;
}

bool Tile::isFilled() const
{
	return m_type != EMPTY;
}

sf::Vector2f Tile::getSize() const
{
	return m_size;
}
