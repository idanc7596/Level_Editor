#pragma once
#include <SFML/Graphics.hpp>

//constants for drawing:
const int WINDOW_HEIGHT = 750, WINDOW_WIDTH = 1000;
const int MARGIN_SIZE = 50;
const int SPACE_SIZE = 5;
const int NUM_OF_ICONS = 14;

//types codes for all objects:
const int NOT_CLICKED = -1;
const int KING = 0,
		  MAGE = 1, 
		  WARRIOR = 2, 
		  THIEF = 3,
	      WALL = 4, 
		  GATE = 5, 
		  FIRE = 6, 
		  ORC = 7, 
		  KEY = 8, 
		  TELEPORT = 9, 
		  THRONE = 10,
	      ERASE = 11, 
	   	  CLEAR = 12, 
		  SAVE = 13,
          EMPTY = -1;


//objects representing chars for writing in file: 
const char EMPTY_CHAR = ' ',
		   KING_CHAR = 'K',
           MAGE_CHAR = 'M',
           WARRIOR_CHAR = 'W',
           THIEF_CHAR = 'T',
           WALL_CHAR = '=',
           GATE_CHAR = '#',
           FIRE_CHAR = '*',
           ORC_CHAR = '!',
           KEY_CHAR = 'F',
           TELEPORT_CHAR = 'X',
           THRONE_CHAR = '@';


//for pop up window input:
const int DELETE_KEY = 8;
const int ENTER_KEY = 13;
const int CHARS_RANGE = 128;
