#include "Date.h"

void Date::setDate(int year, int month, int day)
{
	Date::year = year;
	Date::month = month;
	Date::day = day;
}
void Date::printDate()
{
	std::cout << Date::year << "�� " << Date::month << "�� " << Date::day << "��" << std::endl;
}

int Date::getYear()
{
	return Date::year;
}
int Date::getMonth()
{
	return Date::month;
}
int Date::getDay()
{
	return Date::day;
}

Date::Date(int year, int month, int day)
{
	Date::year = year;
	Date::month = month;
	Date::day = day;
}

Date::Date()
{
	Date::year = 2018;
	Date::month = 6;
	Date::day = 24;
}


Date::~Date()
{
}
