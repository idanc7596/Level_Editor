#include "Menu.h"

Menu::Menu()
	: m_clickedButton(nullptr), 
	  m_size(sf::Vector2f(MENU_WIDTH, MENU_HEIGHT)),
	  m_position(sf::Vector2f(MARGIN_SIZE, MARGIN_SIZE)),
	  m_buttons() 
{
}

//create the buttons vector with appropriate textures:
void Menu::setTextures(const std::vector<sf::Texture>& textures)
{
	int buttonEdge = (MENU_WIDTH-NUM_OF_ICONS*SPACE_SIZE) / NUM_OF_ICONS;
	sf::Vector2f buttonSize(buttonEdge, buttonEdge);
	sf::Vector2f currentButtonPosition(m_position);
	for (int i = 0; i < NUM_OF_ICONS; i++) {
		Button currentButton(i, &textures[i], buttonSize, currentButtonPosition);
		m_buttons.push_back(currentButton);
		currentButtonPosition.x += buttonEdge + SPACE_SIZE;
	}
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < NUM_OF_ICONS; i++) {
		target.draw(m_buttons[i]);
	}
}

bool Menu::wasClicked(const sf::Vector2f& clickPosition)
{
	for (int i = 0; i < NUM_OF_ICONS; i++) {
		if (m_buttons[i].wasClicked(clickPosition)) {
			return true;
		}
	}
	return false;
}

bool Menu::wasHovered(const sf::Vector2f& mousePosition)
{
	for (int i = 0; i < NUM_OF_ICONS; i++) {
		if (m_buttons[i].wasHovered(mousePosition)) {
			return true;
		}
	}
	return false;
}

void Menu::handleClick(const sf::Vector2f& clickPosition)
{
	for (int i = 0; i < NUM_OF_ICONS; i++) {
		if (m_buttons[i].wasClicked(clickPosition)) {
			//there is previous clicked button:
			if (m_clickedButton != nullptr && m_clickedButton != &m_buttons[i]) { 
				m_clickedButton->setAsNotClicked();
			}
			m_clickedButton = &m_buttons[i];
		}
	}
}

const Button* Menu::getClickedButton() const
{
	return m_clickedButton;
}
