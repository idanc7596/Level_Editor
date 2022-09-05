#include "Button.h"

Button::Button(int type, const sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
	: m_type(type), m_isClicked(false), m_texture(texture), m_size(size), m_position(position)
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->createShape());
}

bool Button::wasClicked(const sf::Vector2f& clickPosition)
{
	if (this->createShape().getGlobalBounds().contains(clickPosition)) {
		m_isClicked = true;
		return true;
	}
	return false;
}

//check if mouse cursor hovers over the button:
bool Button::wasHovered(const sf::Vector2f& mousePosition)
{
	if (this->createShape().getGlobalBounds().contains(mousePosition)) {
		return true;
	}
	return false;
}

int Button::getType() const
{
	return m_type;
}

void Button::setAsNotClicked()
{
	m_isClicked = false;
}

//create a rectangle shape that represents the button:
sf::RectangleShape Button::createShape() const
{
	sf::RectangleShape rec(m_size);
	rec.setPosition(m_position);
	
	if (!m_isClicked) {
		rec.setTexture(m_texture);
		rec.setOutlineThickness(1.f);
		rec.setOutlineColor(sf::Color::Black);
	}
	else { //if clicked, draw highlighted
		rec.setOutlineThickness(2.f);
		rec.setOutlineColor(sf::Color::Blue);
		rec.setFillColor(sf::Color(240,250,255));
		rec.setTexture(m_texture);
	}

	return rec;
}

