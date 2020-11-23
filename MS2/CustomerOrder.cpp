// Name: Juyoung Park
// Seneca Student ID: 150155182
// Seneca email: jpark214@myseneca.ca
// Date of completion: 11/22/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <vector>
#include <utility>
#include "CustomerOrder.h"
using namespace std;

//static variable initialization
size_t CustomerOrder::m_widthField = 0;

//custom constr
CustomerOrder::CustomerOrder(const string& record)
{
	//use an Utilities object
	Utilities utility;
	size_t next_pos = 0;
	bool more = true;

	//extract customer name
	this->m_name = utility.extractToken(record, next_pos, more);
	//extract product name
	this->m_product = utility.extractToken(record, next_pos, more);

	//temporary container to store the item tokens in the record
	vector<string> items;
	while (more)
	{
		//keep extracting until there's no more to extract
		items.push_back(utility.extractToken(record, next_pos, more));
	}
	//the #of items in the container
	this->m_cntItem = items.size();

	//dynamically allcate m_lstItem (array of pointers) 
	m_lstItem = new Item * [m_cntItem];
	for (unsigned int i = 0; i < m_cntItem; i++)
	{
		//each element of the m_lstItem is Item pointer type
		this->m_lstItem[i] = new Item(items[i]);
	}

	//update this->m_widthField
	if (m_widthField < utility.getFieldWidth())
		m_widthField = utility.getFieldWidth();
}
//copy constr - throw an exception
CustomerOrder::CustomerOrder(const CustomerOrder& src) 
{
	throw "copy constr deleted";
}
//move operations - 'promise' it doesn't throw exceptions
CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept 
{
	*this = std::move(src);
}
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept 
{
	if (this != &src)
	{
		this->m_name = src.m_name;
		this->m_product = src.m_product;
		
		if (m_lstItem != nullptr)
		{
			//delete each pointer element in the array
			for (unsigned int i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
			//delete pointer ARRAY
			delete[] m_lstItem;
			m_lstItem = nullptr;
		}

		this->m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;
		src.m_lstItem = nullptr;
		src.m_cntItem = 0;
	}
	return *this;
}
CustomerOrder::~CustomerOrder() 
{
	if (m_lstItem != nullptr)
	{
		//delete each pointer element in the array
		for (unsigned int i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		//delete pointer ARRAY
		delete[] m_lstItem;
	}
}
//true if all the items in the order have been filled
bool CustomerOrder::isOrderFilled() const 
{
	bool filled = true;
	for (unsigned int i = 0; i < this->m_cntItem && filled; i++)
	{
		filled = this->m_lstItem[i]->m_isFilled;
	}
	return filled;
}
//returns the ItemInfo::m_fillState(?) of the Item specified as a parameter
bool CustomerOrder::isItemFilled(const string& itemName) const 
{
	bool found = false;
	bool filled = false;
	for (unsigned int i = 0; i < this->m_cntItem && !found; i++)
	{
		if (this->m_lstItem[i]->m_itemName == itemName)
		{
			found = true;
			filled = this->m_lstItem[i]->m_isFilled;
		}	
	}
	return filled;
}
//fills the item in the current order that corresponds to the station passed into the function
void CustomerOrder::fillItem(Station& station, ostream& os) 
{
	for (unsigned int i = 0; i < this->m_cntItem; i++)
	{
		//if the order contains items handled at the station, and the inventory contains at least one element,
		if (this->m_lstItem[i]->m_itemName == station.getItemName())
		{
			if (station.getQuantity() > 0)
			{
				//subtracts qty-1
				station.updateQuantity();
				//updates Item::m_serialNumberand Item::m_isFilled
				this->m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				this->m_lstItem[i]->m_isFilled = true;

				//prints the message Filled NAME, PRODUCT [ITEM_NAME].
				os << "    Filled " << this->m_name
					<< ", " << this->m_product
					<< " [" << this->m_lstItem[i]->m_itemName << "]" << endl;
			}
			else //if the inventory is empty
			{
				//prints the message `Unable to fill NAME, PRODUCT[ITEM_NAME].`
				os << "Unable to fill " << this->m_name
					<< ", " << this->m_product
					<< " [" << this->m_lstItem << "]" << endl;
			}
		}
	}
}
//display the state of the current object in the format
void CustomerOrder::display(ostream& os) const 
{
	/* displays the state of the current object in the format
	STATUS is either FILLED or MISSING*/
	os << this->m_name <<" - "<< this->m_product << endl;
	for (unsigned int i = 0; i < this->m_cntItem; i++)
	{
		os << "[" << setfill('0') << right << setw(6) << this->m_lstItem[i]->m_serialNumber << "] ";
		os << setfill(' ') << left << setw(this->m_widthField) << m_lstItem[i]->m_itemName;
		if (this->m_lstItem[i]->m_isFilled)
			os << " - FILLED";
		else
			os << " - MISSING";
		os << endl;
	}

}