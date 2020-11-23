// Name: Juyoung Park
// Seneca Student ID: 150155182
// Seneca email: jpark214@myseneca.ca
// Date of completion: 11/22/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#include <iostream>
#include <string>
#include "Station.h"
#include "Utilities.h"

struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder //manages a single order on the assembly line
{
	std::string m_name{}; //the name of the customer
	std::string m_product{}; //the name of the product being assembled
	unsigned int m_cntItem{0}; //a count of the #of items for the customer's order
	Item** m_lstItem{nullptr}; //array of pointers(dynamic)
	static size_t m_widthField; //the max width of a field for displaying

public:
	//default constr - defined
	CustomerOrder(){}
	~CustomerOrder();
	CustomerOrder(const std::string& );
	CustomerOrder(const CustomerOrder&);
	//copy assignment operator= - delete
	CustomerOrder& operator=(const CustomerOrder&) = delete;
	CustomerOrder(CustomerOrder&&) noexcept;
	CustomerOrder& operator=(CustomerOrder&&) noexcept;
	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
};