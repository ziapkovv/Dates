/*
 * Date.cpp
 *
 *  Created on: May 18, 2015
 *      Author: zyapkov
 */

#include <iostream>
#include "Date.h"
#include "PairHolidays.h"
using namespace std;

int main() {
	// примерна програма
	Date date1(31, 1, 2015); // създава обект от клас Date
	cout << date1.getDayOfWeek() << endl; // извежда кой ден от седмицата е
	date1 += 1;
	cout << date1 << endl;
	date1 = date1 + 1;
	cout << date1 << endl;
	date1 -= 1;
	cout << date1 << endl;
	date1 = date1 - 1;
	cout << date1 << endl;
	date1 = date1 * 1;
	cout << date1 << endl;
	date1.ChangeMode1(); // променя режима на работа така че да смята само с работни дни
	date1 = date1 + 1;
	cout << date1 << endl; // 29 февруари 2015 е почивен ден
	date1.ChangeMode1();
	Date date2(15, 4, 2014);
	date2.ChangeMode2();
	date2 = date2 + 4;
	cout << date2 << endl;

	return 0;
}

