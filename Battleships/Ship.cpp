#include "Ship.h"

Ship::Ship(ShipType shipType) : m_shipType(shipType), m_damaged(false) {

}

Ship::Ship() : Ship(ShipType::Null) {

}

std::string Ship::getStrRepr() {
	switch (m_shipType)
	{
	case ShipType::Null:
		return "";
	case ShipType::Destroyer:
		return "des";
	case ShipType::Submarine:
		return "sub";
	case ShipType::Cruiser:
		return "cru";
	case ShipType::Battleship:
		return "bat";
	case ShipType::Carrier:
		return "car";
	default:
		return "";
	}
}

void Ship::setDamaged(bool value) {
	m_damaged = value;
}

bool Ship::isDamaged() {
	return m_damaged;
}

ShipType Ship::getType()
{
	return m_shipType;
}

void Ship::setType(ShipType shipType) {
	m_shipType = shipType;
}