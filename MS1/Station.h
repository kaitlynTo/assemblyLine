// Name: Juyoung Park
// Seneca Student ID: 150155182
// Seneca email: jpark214@myseneca.ca
// Date of completion: 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <string>
#include "Utilities.h"

class Station 
{
	int m_stationID{0};
	std::string m_itemName{};
	std::string m_station_desc{};
	int m_serialNumber{ 0 };
	int m_qtyInStock{ 0 };
	static size_t m_widthField;
	static int m_id_generator;
public:
	Station(const std::string&); //custom constr
	const std::string& getItemName()const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream&, bool) const;
};