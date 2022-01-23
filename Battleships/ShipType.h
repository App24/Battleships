#pragma once

// The different ship types that can be present on the board
enum class ShipType {
	Null,
	Destroyer,
	Submarine,
	Cruiser,
	Battleship,
	Carrier,
	SelectorOcean,
	Selector,
	Shot
};

// The str version of the ship types, allows for easy printing to the console
static const char* ship_type_str[] =
{ "Null", "Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier", "Selector" , "Selector", "Shot"};

// The ship size for each ship size, easy way of placing multiple ships at a time
static const int* shipSizes = new int[9]{ 0, 2, 3, 3, 4, 5, 0, 0, 0 };