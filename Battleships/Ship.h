#pragma once
#include <string>
#include "ShipType.h"

class Ship {
public:
	Ship(ShipType shipType);
	Ship();

	std::string getStrRepr();

	void setDamaged(bool value);
	bool isDamaged();

	ShipType getType();
	void setType(ShipType shipType);
private:
	ShipType m_shipType;
	bool m_damaged;
};