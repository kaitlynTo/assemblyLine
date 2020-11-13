// Name: Juyoung Park
// Seneca Student ID: 150155182
// Seneca email: jpark214@myseneca.ca
// Date of completion: 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include "Utilities.h"
using namespace std;

char Utilities::m_delimiter = '\0';

void Utilities::setFieldWidth(size_t newWidth)
{
	this->m_widthField = newWidth;
}
size_t Utilities::getFieldWidth() const
{
	return this->m_widthField;
}
string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
{
	string token{}; //will be extracted token
	size_t delimAt = str.find(m_delimiter,next_pos); //find where the delimiter at
	if (delimAt == string::npos) //if there's no delimiter
	{
		token = str.substr(next_pos, str.length()); //just extract whole token
		more = false; //there's nothing more to extract
	}
	else //if there's delimiter existed
	{
		token = str.substr(next_pos, delimAt-next_pos); //extract token before the delimiter
		more = true; //and there's more to extract
		next_pos = delimAt + 1;
		size_t nextDelimAt = str.find(m_delimiter, delimAt + 1);
		if (next_pos != string::npos && str.substr(next_pos, nextDelimAt - next_pos).empty())
		{
			more = false;
			throw "There is no token between delimiters!";
		}
	}

	//update the width field of the token if needed
	if (m_widthField < token.length())
	{
		m_widthField = token.length();
	}


	return token;
}
void Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;
}
char Utilities::getDelimiter()
{
	return m_delimiter;
}