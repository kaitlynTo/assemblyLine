// Name: Juyoung Park
// Seneca Student ID: 150155182
// Seneca email: jpark214@myseneca.ca
// Date of completion: 11/13/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Station.h"
using namespace std;
//static member initialization 
size_t Station::m_widthField = 0;
int Station::m_id_generator = 0;



//custom constr
Station::Station(const std::string& record)
{
	m_stationID = ++m_id_generator;

	Utilities util;
	size_t next_pos = 0;
	bool more = true;
	try 
	{
		if (more)
		{
			//extract m_itemName
			m_itemName = util.extractToken(record, next_pos, more);
			//extract startingSerial#
			m_serialNumber = stoi(util.extractToken(record, next_pos, more));
			//extract qty in stock
			m_qtyInStock = stoi(util.extractToken(record, next_pos, more));
			if (m_widthField < util.getFieldWidth())
			{
				//set the widthField to the max width
				m_widthField = util.getFieldWidth();
			}
			//extract description
			m_station_desc = util.extractToken(record, next_pos, more);
		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}
//query item name
const std::string& Station::getItemName()const
{
	return m_itemName;
}
//query next serial number and increments +1
unsigned int Station::getNextSerialNumber()
{
	return m_serialNumber++;
}
//get quantity in stock
unsigned int Station::getQuantity() const
{
	return m_qtyInStock;
}
//subtract -1 from the available qty in stock (shouldn't be less than 0)
void Station::updateQuantity()
{
	if (m_qtyInStock > 0)
		m_qtyInStock--;
}
//based on full condition, display with formatting
void Station::display(std::ostream& os, bool full) const
{
	os << "[" << right << setw(3) << setfill('0') << m_stationID << "]";
	os << " Item: " << left << setw(m_widthField) <<setfill(' ') << getItemName();
	os << " [" << right << setw(6) << setfill('0') << m_serialNumber << "]";

	if (full)
	{
		os << " Quantity: " << left << setw(m_widthField) << setfill(' ') << m_qtyInStock;
		os << " Description: " << m_station_desc;
	}

	os << endl;
}