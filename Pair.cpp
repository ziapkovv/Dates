/*
 * Pair.cpp
 *
 *  Created on: May 24, 2015
 *      Author: zyapkov
 */

#include "PairHolidays.h"
#include <iostream>
using namespace std;

const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

PairHolidays::PairHolidays(int d, int m) {
	setPair(d, m);
}

void PairHolidays::setPair(int _day, int _month) {
	if (_month >= 1 && _month <= 12)
		month = _month;
	else {
		cout << "Невалидни данни ! Месецът е променен на 1." << endl;
		month = 1;
	}
	if (_day >= 1 && _day <= daysInMonth[month])
			day = _day;
		else
			day = 1;
	if (month == 2 && _day ==29)
		day = _day;
}

int PairHolidays::getDay()const{
	return day;
}

int PairHolidays::getMonth()const{
	return month;
}

PairHolidays& PairHolidays::operator-(int _days){
	day = day - _days;
	return *this;
}

void PairHolidays::print() const {
	cout << "Pair(day-month) : " << day << "-" << month << endl;
}
