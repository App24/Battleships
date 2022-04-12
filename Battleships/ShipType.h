#pragma once

enum class ShipType {
	Empty,
	Destroyer,
	Submarine,
	Cruiser,
	Battleship,
	Carrier,
	Shot,
	Selection,
	WaterSelection
};

static const char* shipTypeString[] = {
	"",
	"Destroyer",
	"Submarine",
	"Cruiser",
	"Battleship",
	"Carrier"
};

static const char* shortShipString[] = {
	"",
	"des",
	"sub",
	"cru",
	"bat",
	"car",
	" x ",
	" + ",
	" + "
};

static const int shipSizes[] = {
	0,
	2,
	3,
	3,
	4,
	5,
	0,
	0,
	0
};