#pragma once

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

static const char* ship_type_str[] =
{ "Null", "Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier", "Selector" , "Selector", "Shot"};

static const int* shipSizes = new int[9]{ 0, 2, 3, 3, 4, 5, 0, 0, 0 };