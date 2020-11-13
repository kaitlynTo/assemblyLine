// Name: Juyoung Park
// Seneca Student ID: 150155182
// Seneca email: jpark214@myseneca.ca
// Date of completion: 11/13/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <string>

class Utilities 
{
	size_t m_widthField{ 1 }; //the length of a token extracted
	static char m_delimiter;
public:
	void setFieldWidth(size_t newWidth);
	size_t getFieldWidth() const;
	std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(char newDelimiter);
	static char getDelimiter();
};