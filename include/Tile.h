#pragma once
#include <SFML/Graphics.hpp>
#include "macros.h"

class Tile : public sf::Drawable
{
public:
	Tile(sf::Vector2f size, sf::Vector2f position,
		int type = EMPTY, sf::Texture *texture = nullptr);
	sf::RectangleShape createShape() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void reset();
	bool isFilled() const;
	sf::Vector2f getSize() const;
	void setTexture(const sf::Texture *texture); 
	const sf::Texture* getTexture() const;
	void setType(int type);
	int getType() const;

private:
	int m_type;  
	const sf::Texture *m_texture;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
};