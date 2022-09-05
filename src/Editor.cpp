#include "Editor.h"
#include <iostream>
#include <sstream>

Editor::Editor() 
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
		       "Save the King - Level Editor", sf::Style::Close),
	  m_textures(),
	  m_menu(),
	  m_grid()
{
	loadTextures();
	m_menu.setTextures(m_textures);
	m_file.open("Board.txt");
	if (m_file.is_open()) { //file exists
		copyFileToGrid();
	}
}

Editor::~Editor()
{
	m_file.close();
}

//if file exists, copy its content to the grid:
void Editor::copyFileToGrid()
{
	int rows, cols;
	m_file >> rows >> cols;
	m_grid.init(rows, cols);

	std::string str;
	m_file.get(); //read first '\n'
	std::getline(m_file, str); //read blank line and second '\n'

	//reads all file:
	char c;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c = m_file.get();
			switch (c) {
			case KING_CHAR:
				m_grid.setTile(i, j, KING, &m_textures[KING]);
				break;
			case MAGE_CHAR:
				m_grid.setTile(i, j, MAGE, &m_textures[MAGE]);
				break;
			case WARRIOR_CHAR:
				m_grid.setTile(i, j, WARRIOR, &m_textures[WARRIOR]);
				break;
			case THIEF_CHAR:
				m_grid.setTile(i, j, THIEF, &m_textures[THIEF]);
				break;
			case WALL_CHAR:
				m_grid.setTile(i, j, WALL, &m_textures[WALL]);
				break;
			case GATE_CHAR:
				m_grid.setTile(i, j, GATE, &m_textures[GATE]);
				break;
			case FIRE_CHAR:
				m_grid.setTile(i, j, FIRE, &m_textures[FIRE]);
				break;
			case ORC_CHAR:
				m_grid.setTile(i, j, ORC, &m_textures[ORC]);
				break;
			case KEY_CHAR:
				m_grid.setTile(i, j, KEY, &m_textures[KEY]);
				break;
			case TELEPORT_CHAR:
				m_grid.setTile(i, j, TELEPORT, &m_textures[TELEPORT]);
				break;
			case THRONE_CHAR:
				m_grid.setTile(i, j, THRONE, &m_textures[THRONE]);
				break;
			default:
				break;
			}
		}
		m_file.get(); //read '\n'
	}
}

//file doesn't exist. ask user for grid dimensions.
//(user input should be inserted in the window itself).
void Editor::popUpWindowInput() 
{
	sf::RenderWindow popUpWindow(sf::VideoMode(POP_UP_WINDOW_WIDTH, POP_UP_WINDOW_HEIGHT), "",
								 sf::Style::None | sf::Style::Titlebar);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text("Please enter level's height and width\n                (in this window)", font);
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2.f,
								text.getLocalBounds().height / 2.f));
	text.setPosition(sf::Vector2f(POP_UP_WINDOW_WIDTH / 2,
								  POP_UP_WINDOW_HEIGHT / 2 - 0.5 * MARGIN_SIZE));
	text.setFillColor(sf::Color::Black);

	int rows = 0, cols = 0;
	std::string str;
	sf::Text input(str, font);
	input.setFillColor(sf::Color::Blue);
	input.setPosition(sf::Vector2f(POP_UP_WINDOW_WIDTH / 2, 
								   POP_UP_WINDOW_HEIGHT / 2 + 0.6 * MARGIN_SIZE));
	
	bool inputInserted = false;
	while (popUpWindow.isOpen() && !inputInserted)
	{
		sf::Event ev;
		while (popUpWindow.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::TextEntered:
				if (ev.text.unicode < CHARS_RANGE && 
					ev.text.unicode != DELETE_KEY &&
					ev.text.unicode != ENTER_KEY) {
					str += ev.text.unicode; //add the text entered to str
				}
				//clear last character from str
				else if (ev.text.unicode == DELETE_KEY) {
					if (!str.empty()) {
						str = str.substr(0, str.length() - 1);
					}
				}
				else if (ev.text.unicode == ENTER_KEY) {
					inputInserted = true;
				}
				
				//for centering
				input.setOrigin(sf::Vector2f(input.getLocalBounds().width / 2.f,
					input.getLocalBounds().height / 2.f));
				input.setString(str); //update the displayed text
				break;
			default:
				break;
			}		
		}
		
		popUpWindow.clear(sf::Color::White);
		popUpWindow.draw(text);
		popUpWindow.draw(input);
		popUpWindow.display();
	}

	std::istringstream stringStream(str); 
	stringStream >> rows >> cols; //extract the dimensions
	m_grid.init(rows, cols);
}

//the main loop:
void Editor::run()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_menu);
	m_window.display();
	if(!m_file.is_open()) { //file doesn't exist
		popUpWindowInput();
	}

	//main events loop:
	while (m_window.isOpen())
	{
		sf::Event ev;
		while (m_window.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased: 
				handleClick(ev.mouseButton);
				break;
			case sf::Event::MouseMoved: 
				m_mousePosition = sf::Vector2f(ev.mouseMove.x, ev.mouseMove.y);
				break;
			default:
				break;
			}				
		}

		m_window.clear(sf::Color::White);
		m_window.draw(m_menu);
		m_window.draw(m_grid);
		drawHoveredIcon();
		m_window.display();
	}
}

void Editor::handleClick(const sf::Event::MouseButtonEvent& ev) 
{

	sf::Vector2f clickPosition(m_window.mapPixelToCoords({ev.x, ev.y}));
	if (m_menu.wasClicked(clickPosition)) {
		m_menu.handleClick(clickPosition);
	}
	else if(m_grid.wasClicked(clickPosition) && 
		    m_menu.getClickedButton() != nullptr) {
		m_grid.handleClick(m_menu.getClickedButton(), clickPosition, 
						   m_menu.getClickedButton()->getType(), 
						   &m_textures[m_menu.getClickedButton()->getType()]);
	}

	//clear:
	if (m_menu.getClickedButton() != nullptr && 
		m_menu.getClickedButton()->getType() == CLEAR) {
		m_grid.reset();
		m_window.clear(sf::Color::White);
		m_window.draw(m_menu);
		m_window.draw(m_grid);
		drawHoveredIcon();
		m_window.display();
		popUpWindowInput();
	}
	//save:
	else if (m_menu.getClickedButton() != nullptr &&
			 m_menu.getClickedButton()->getType() == SAVE) {
		save();
	}
}

//save the grid content to the file, according to the format described in README.
void Editor::save()
{
	m_file.close();
	//truncate file:
	m_file.open("Board.txt", std::fstream::out | std::fstream::trunc);
	
	m_file << m_grid.getNumOfRows() << " " << m_grid.getNumOfCols() << "\n\n";
	for (int i = 0; i < m_grid.getNumOfRows(); i++) {
		for (int j = 0; j < m_grid.getNumOfCols(); j++) {
			switch (m_grid.getTileType(i,j)) {
			case EMPTY:
				m_file << EMPTY_CHAR;
				break;
			case KING:
				m_file << KING_CHAR;
				break;
			case MAGE:
				m_file << MAGE_CHAR;
				break;
			case WARRIOR:
				m_file << WARRIOR_CHAR;
				break;
			case THIEF:
				m_file << THIEF_CHAR;
				break;
			case WALL:
				m_file << WALL_CHAR;
				break;
			case GATE:
				m_file << GATE_CHAR;
				break;
			case FIRE:
				m_file << FIRE_CHAR;
				break;
			case ORC:
				m_file << ORC_CHAR;
				break;
			case KEY:
				m_file << KEY_CHAR;
				break;
			case TELEPORT:
				m_file << TELEPORT_CHAR;
				break;
			case THRONE:
				m_file << THRONE_CHAR;
				break;
			default:
				break;
			}
		}
		m_file << "\n"; //new line
	}

	m_file.flush(); //update content 'online'
}

//draw the icon that hover with mouse cursor:
void Editor::drawHoveredIcon()
{
	if ( m_menu.getClickedButton() != nullptr &&
		m_menu.getClickedButton()->getType() != CLEAR &&
		m_menu.getClickedButton()->getType() != SAVE &&
		(m_menu.getClickedButton()->getType() == ERASE || !m_grid.isFilledTile(m_mousePosition)) &&
		!m_menu.wasHovered(m_mousePosition)) {
		m_window.draw(createHoveredIcon());
	}
}


sf::Sprite Editor::createHoveredIcon() const
{
	sf::Sprite hoveredIcon;
	hoveredIcon.setTexture(m_textures[m_menu.getClickedButton()->getType()]);
	hoveredIcon.setColor(sf::Color(255, 255, 255, 150)); //white opacity
	hoveredIcon.setPosition(m_mousePosition);
	hoveredIcon.setOrigin(sf::Vector2f(hoveredIcon.getLocalBounds().width / 2.f,
		                               hoveredIcon.getLocalBounds().height / 2.f));
	//sets hovered icon size to match tile size:
	float factor = m_grid.getTileSize().x / hoveredIcon.getLocalBounds().width;
	hoveredIcon.setScale(sf::Vector2f(factor, factor));
	return hoveredIcon;
}


void Editor::loadTextures()
{
	sf::Texture textures[NUM_OF_ICONS];
	
	textures[KING].loadFromFile("king.png");
	textures[MAGE].loadFromFile("mage.png");
	textures[WARRIOR].loadFromFile("warrior.png");
	textures[THIEF].loadFromFile("thief.png");
	textures[WALL].loadFromFile("wall.png");
	textures[GATE].loadFromFile("gate.png");
	textures[FIRE].loadFromFile("fire.png");
	textures[ORC].loadFromFile("orc.png");
	textures[KEY].loadFromFile("key.png");
	textures[TELEPORT].loadFromFile("teleport.png");
	textures[THRONE].loadFromFile("throne.png");
	textures[ERASE].loadFromFile("erase.png");
	textures[CLEAR].loadFromFile("clear.png");
	textures[SAVE].loadFromFile("save.png");

	for (int i = 0; i < NUM_OF_ICONS; i++) {
		m_textures.push_back(textures[i]);
	}
}

