#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "macros.h"

//constants used for drawing:
const int MENU_WIDTH = WINDOW_WIDTH - 2 * MARGIN_SIZE;
const int MENU_HEIGHT = MENU_WIDTH / NUM_OF_ICONS;

class Menu : public sf::Drawable
{
public:
	Menu();
	void setTextures(const std::vector<sf::Texture>& textures);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool wasClicked(const sf::Vector2f& clickPosition);
	bool wasHovered(const sf::Vector2f& mousePosition);
	void handleClick(const sf::Vector2f& clickPosition);
	const Button* getClickedButton() const;


private:
	std::vector<Button> m_buttons;
	Button *m_clickedButton;

	sf::Vector2f m_size;
	sf::Vector2f m_position;
};