#pragma once
#include "ShipType.h"
#include <string>

class Ship {
public:
	Ship(ShipType shipType);
	Ship();

	// Get the 3 char wide representation of the ship
	std::string getStrRepr();

	void setDamaged(bool value);
	bool isDamaged();

	ShipType getType();
	void setType(ShipType shipType);
private:
	ShipType m_shipType;
	bool m_damaged;
};