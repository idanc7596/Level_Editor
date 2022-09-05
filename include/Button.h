#pragma once
#include <SFML/Graphics.hpp>
#include "macros.h"

class Button : public sf::Drawable
{
public:
	Button(int type, const sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool wasClicked(const sf::Vector2f& clickPosition);
	bool wasHovered(const sf::Vector2f& mousePosition);
	int getType() const;
	void setAsNotClicked();

private:
	sf::RectangleShape createShape() const;

	int m_type = NOT_CLICKED;
	bool m_isClicked;
	const sf::Texture *m_texture;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
};