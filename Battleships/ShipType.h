#pragma once

enum class ShipType {
	Null,
	Destroyer,
	Submarine,
	Cruiser,
	Battleship,
	Carrier
};

static const char* ship_type_str[] =
{ "Null", "Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier" };