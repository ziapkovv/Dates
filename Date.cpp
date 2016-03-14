/*
 * Date.cpp
 *
 *  Created on: May 18, 2015
 *      Author: zyapkov
 */
#include <iostream>
#include <ctime>
#include "Date.h"
#include "PairHolidays.h"
#include <cstdlib> //за exit(1)
using namespace std;

//масив, съдържащ броя на дните за всеки месец
//нулевият елемент не се използва
const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//масив, съдържащ имената на дните от седмицата
// неделята е с индекс  0 , понеделник е с 1 ...
const char *NameOfDay[] = { "неделя", "понеделник", "вторник", "сряда",
		"четвъртък", "петък", "събота" };
// съдържа имената на месеците
// първия елемент не се използва
const char *NameOfMonth[] = { "", "януари", "февруари", "март", "април", "май",
		"юни", "юли", "август", "септември", "октомври", "ноември", "декември" };
const PairHolidays Holidays[] = { PairHolidays(1, 1), PairHolidays(3, 3),
		PairHolidays(1, 5), PairHolidays(6, 5), PairHolidays(24, 5),
		PairHolidays(6, 9), PairHolidays(22, 9), PairHolidays(1, 11),
		PairHolidays(24, 12), PairHolidays(25, 12), PairHolidays(26, 12) };

// констурктор
Date::Date(int d, int m, int y) {
	Mode1 = 0;
	Mode2 = 0;
	setDate(d, m, y);
}

// мутатор за ден, месец, година
void Date::setDate(int _day, int _month, int _year) {
	if (_month >= 1 && _month <= 12)
		month = _month;
	else {
		cout << "Невалидни данни ! Месецът е променен на 1." << endl;
		month = 1;
	}
	//1916 година Григорианския календар е въведен в България
	if (_year >= 1916)
		year = _year;
	else {
		cout << "Невалидни данни ! Годината е променена на 2015." << endl;
		year = 2015;
	}
	if (month == 2 && leapYear(year)) {
		if (_day >= 1 && _day <= 29)
			day = _day;
		else {
			cout << "Невалидни данни за ден ! Денят е променен на 1." << endl;
			day = 1;
		}
	} else {
		if (_day >= 1 && _day <= daysInMonth[month])
			day = _day;
		else {
			cout << "Невалидни данни за ден ! Денят е променен на 1." << endl;
			day = 1;
		}
	}
}

// copy конструктор
Date::Date(const Date &other) {
	Mode1 = 0;
	Mode2 = 0;
	day = other.day;
	month = other.month;
	year = other.year;
}

// селектор за година
int Date::getYear() const {
	return year;
}

//селектор за месец
int Date::getMonth() const {
	return month;
}

//селектор за ден
int Date::getDay() const {
	return day;
}

int Date::WeeksToDays(int weeks) const {
	return weeks * 7;
}

// мутатор на ден
void Date::setDay(int _day) {
	if (month == 2 && leapYear(year)) {
		if (_day >= 1 && _day <= 29)
			day = _day;
		else
			cout << "Невалидни данни за ден ! Денят остава непроменен." << endl;
	} else {
		if (_day >= 1 && _day <= daysInMonth[month])
			day = _day;
		else
			cout << "Невалидни данни за ден ! Денят остава непроменен." << endl;
	}
}

//мутатро на месец
void Date::setMonth(int _month) {
	if (_month >= 1 && _month <= 12)
		month = _month;
	else
		cout << "Невалидни данни ! Месецът остава непроменен." << endl;
}

//мутатро на година
void Date::setYear(int _year) {
	if (year >= 1916)
		year = _year;
	else
		cout << "Невалидни данни ! Годината остава непроменена." << endl;
}

// преминава на следващия ден
void Date::addDay() {
	if (EndOfMonth(day) && month == 12) {
		day = month = 1;
		++year;
	} else if (EndOfMonth(day)) {
		day = 1;
		++month;
	} else
		++day;
}

//преминава на предишния ден
void Date::remDay() {
	if (StartOfMonth(day) && month == 1) {
		day = 31;
		month = 12;
		year--;
	} else if (StartOfMonth(day)) {
		month--;
		if (leapYear(year) && month == 2)
			day = 29;
		else
			day = daysInMonth[month];

	} else
		--day;

}

//преминава с k месеца напред от текущата дата
void Date::addMonth(int k) {
	if (k > 0) {
		while (k > 0) {
			if (LastMonth()) {
				month = 1;
				++year;
			} else
				++month;
			--k;
		}
		if (leapYear(year) && month == 2) {
			if (day > 29)
				day = 29;
		} else if (day > daysInMonth[month]) {
			day = daysInMonth[month];
		}
	} else
		cout << "Некоректен брой месеци ! Датата остава непроменена !" << endl;
}

//преминава с k месеца назад от текущата дата
void Date::remMonth(int k) {
	if (k > 0) {
		while (k > 0) {
			if (FirstMonth()) {
				month = 12;
				--year;
			} else
				--month;
			--k;
		}
		if (leapYear(year) && month == 2) {
			if (day > 29)
				day = 29;
		} else if (day > daysInMonth[month]) {
			day = daysInMonth[month];
		}
	} else
		cout << "Некоректен брой месеци ! Датата остава непроменена !" << endl;
}

//добавя k на брой година към текущата
void Date::addYear(int k) {
	if (k > 0) {
		if (month == 2 && EndOfMonth(day) && leapYear(year) && k % 4 != 0) {
			cout << "Месец февруари съдържа 28 дни. Денят е променен на 28-ми."
					<< endl;
			day = 28;
		}
		year = year + k;

	} else
		cout << "Некоректен брой години ! Датата остава непроменена." << endl;
}

//изважда к на брой години от текущата дата
void Date::remYear(int k) {
	if (k > 0 && (year - k >= 1916)) {
		if (month == 2 && EndOfMonth(day) && leapYear(year) && k % 4 != 0) {
			cout << "Месец февруари съдържа 28 дни. Денят е променен на 28-ми."
					<< endl;
			day = 28;
		}
		year = year - k;
	} else
		cout << "Некоректен брой години ! Датата остава непроменена." << endl;
}

// функция проверяваща дали дадена година е високосна
bool Date::leapYear(int _year) const {
	return (_year % 400 == 0 || (_year % 100 != 0 && _year % 4 == 0));
}

//проверява дали _day е първия ден от месеца
bool Date::StartOfMonth(int _day) const {
	return _day == 1;
}

//проверява дали _day е последния ден от месеца
bool Date::EndOfMonth(int _day) const {
	if (month == 2 && leapYear(year))
		return _day == 29;
	else
		return _day == daysInMonth[month];
}

// проверява дали месеца е Януари
bool Date::FirstMonth() const {
	return month == 1;
}

// проверява дали месеца е Декември
bool Date::LastMonth() const {
	return month == 12;
}

// проверява дали date1 е по-голяма или равна на date2
bool IsBigger(const Date &date1, const Date &date2) {
	if (date1.getYear() == date2.getYear()) {
		if (date1.getMonth() == date2.getMonth()) {
			return date1.getDay() >= date2.getDay();
		} else
			return date1.getMonth() >= date2.getMonth();
	} else
		return date1.getYear() >= date2.getYear();
}

// проверява дали date1 е същата като date2
bool IsEqual(const Date &date1, const Date &date2) {
	return ((date1.getDay() == date2.getDay())
			&& (date1.getMonth() == date2.getMonth())
			&& (date1.getYear() == date2.getYear()));
}

// селектор за ден от седмицата
// алгоритъма определя
const char* Date::getDayOfWeek() const {
	 static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	 Date temp = *this;
	    temp.year -= temp.month < 3;
	    int k =  ( temp.year + temp.year/4 - temp.year/100 + temp.year/400 + t[temp.month-1] + temp.day) % 7;
	    return NameOfDay[k];
}

// оператор за извеждане на дата
std::ostream& operator<<(std::ostream& out, Date const &date) {
	out << date.getDay() << " " << NameOfMonth[date.getMonth()] << " "
			<< date.getYear() << "г.";
	return out;
}

//оператор за въвеждане на дата
std::istream & operator>>(std::istream & in, Date & date) {
	cout << "Въведете дата, като за разделител трябва да използвате '-' :"
			<< endl;
	int _day, _month, _year;
	char symbol = '-'; // служи за разделител
	in >> _day >> symbol >> _month >> symbol >> _year;
	date.setDate(_day, _month, _year);
	return in;
}

//прибавя _days на брой дни
Date& Date::operator+(int _days) {
	if (_days > 0) {
		if (Mode1 == 1 && Mode2 == 1) {
			cout << "И двата режима работят. Изключете ненужния!" << endl;
			exit(1);
		}
		if (Mode1 == 1) {
			while (_days > 0) {
				this->addDay();
				if (!this->isHoliday())
					--_days;
				this->Mode1 = 1;
			}
		} else {
			while (_days > 0) {
				this->addDay();
				--_days;
			}
			if (Mode2 == 1 && this->isHoliday()) {
				cout << "Въведете параметър за търсене :" << endl;
				cout
						<< "1) Въведете положително число за търсене напред във времето"
						<< endl
						<< "2) Въведете отрицателно число за търсене назад във времето"
						<< endl
						<< "3) Въведете 0 за търсене без значение от посоката"
						<< endl;
				int p; // параметър определящ посоката на търсене
				cin >> p;
				if (!cin) {
					cout << "Некоректни данни!" << endl;
					exit(1);
				}
				*this = this->ClosestWorkDay(p);
				this->Mode2 = 1;
			}
		}
	} else
		cout << "Некоректни данни! Датата остава непроменена." << endl;
	return *this;
}

//увеличава датата с един ден ++date
Date & Date::operator++() {
	addDay();
	if (this->Mode2 && this->isHoliday())
		this->ChangetoMode2();
	return *this;
}

//увеличава датата с един ден date++
Date Date::operator++(int unused) {
	Date temp = *this;
	this->addDay();
	return temp;
}

// увеличава датата с _days дни
Date operator+=(Date &date, int _days) {
	if (_days > 0)
		date = date + _days;
	else
		cout << "Некоректен брой дни ! Датата остава непроменена !" << endl;
	return date;
}

// намалява датата с _days дни
Date operator-=(Date &date, int _days) {
	if (_days > 0)
		date = date - _days;
	else
		cout << "Некоректен брой дни ! Датата остава непроменена !" << endl;
	return date;
}

// намалява датата с _days дни
Date& Date::operator-(int _days) {
	if (_days > 0) {
		if (Mode1 == 1 && Mode2 == 1) {
			cout << "И двата режима работят. Изключете ненужния!" << endl;
			exit(1);
		}
		if (Mode1 == 1) {
			while (_days > 0) {
				this->remDay();
				if (!this->isHoliday())
					--_days;
				this->Mode1 = 1;
			}
		} else {
			while (_days > 0) {
				this->remDay();
				--_days;
			}
			if (Mode2 == 1 && this->isHoliday()) {
				cout << "Въведете параметър за търсене :" << endl;
				cout
						<< "1) Въведете положително число за търсене напред във времето"
						<< endl
						<< "2) Въведете отрицателно число за търсене назад във времето"
						<< endl
						<< "3) Въведете 0 за търсене без значение от посоката"
						<< endl;
				int p; // параметър определящ посоката на търсене
				cin >> p;
				if (!cin) {
					cout << "Некоректни данни!" << endl;
					exit(1);
				}
				*this = this->ClosestWorkDay(p);
				this->Mode2 = 1;
			}
		}
	} else
		cout << "Некоректни данни! Датата остава непроменена." << endl;
	return *this;
}

// намалява датата с един ден --date
Date& Date::operator--() {
	remDay();
	if (this->Mode2 && this->isHoliday())
		this->ChangetoMode2();
	return *this;
}

//намалява датата с един ден date--
Date Date::operator--(int unused) {
	Date temp = *this;
	remDay();
	return temp;
}

//преминава с _months месеца напред от дата
Date operator*=(Date &date, int _months) {
	date.addMonth(_months);
	if (date.Mode2 && date.isHoliday())
		date.ChangetoMode2();
	return date;
}

//преминава с _months месеца напред от дата
Date& Date::operator*(int _months) {
	addMonth(_months);
	if (this->Mode2 && this->isHoliday())
		this->ChangetoMode2();
	return *this;
}

//преминава с _months месеца назад от датата
Date operator/=(Date &date, int _months) {
	date.remMonth(_months);
	if (date.Mode2 && date.isHoliday())
		date.ChangetoMode2();
	return date;
}

//преминава с _month месеца назад от датата
Date& Date::operator/(int _months) {
	remMonth(_months);
	if (this->Mode2 && this->isHoliday())
		this->ChangetoMode2();
	return *this;
}

// добавя _years на брой години към текущата дата
Date& Date::operator&(int _years) {
	addYear(_years);
	if (this->Mode2 && this->isHoliday())
		this->ChangetoMode2();
	return *this;
}

// добавя _years на брой години към текущата дата
Date operator&=(Date &date, int _years) {
	date.addYear(_years);
	if (date.Mode2 && date.isHoliday())
		date.ChangetoMode2();
	return date;
}

// изважда _years на брой години от текущата дата
Date& Date::operator |(int _years) {
	remYear(_years);
	if (this->Mode2 && this->isHoliday())
		this->ChangetoMode2();
	return *this;
}

// изважда _years на брой години от текущата дата
Date operator|=(Date &date, int _years) {
	date.remYear(_years);
	if (date.Mode2 && date.isHoliday())
		date.ChangetoMode2();
	return date;
}

//добавя weeks на брой седмици
Date& Date::operator^(int weeks) {
	if (WeeksToDays(weeks) > 0) {
		int days = WeeksToDays(weeks);
		while (days > 0) {
			addDay();
			days--;
		}
	} else
		cout << "Некоректно въведен брой седмици ! Датата остава непроменена."
				<< endl;
	if (this->Mode2 && this->isHoliday())
		this->ChangetoMode2();
	return *this;
}

// добавя weeks на брой седмици
Date operator^=(Date &date, int weeks) {
	date = date ^ weeks;
	if (date.Mode2 && date.isHoliday())
		date.ChangetoMode2();
	return date;
}

// връща датата с weeks на брой седмици по-назад
Date& Date::operator%(int weeks) {
	if (WeeksToDays(weeks) > 0) {
		int days = WeeksToDays(weeks);
		while (days > 0) {
			remDay();
			days--;
		}
	} else
		cout << "Некоректно въведен брой седмици ! Датата остава непроменена."
				<< endl;
	if (this->Mode2 && this->isHoliday())
		this->ChangetoMode2();
	return *this;
}

// връща датата с weeks на брой седмици по-назад
Date operator%=(Date &date, int weeks) {
	date = date % weeks;
	if (date.Mode2 && date.isHoliday())
		date.ChangetoMode2();
	return date;
}

//връща зарликата между две дати в дни
int operator-(const Date &date1, const Date &date2) {
	if (!IsEqual(date1, date2)) {
		int days = 0; // записва дните мужду date1 и date2
		if (IsBigger(date1, date2)) {
			Date temp = date2; // копираме date2 в temp за да можем да работим с нея
			while (!IsEqual(temp, date1)) {
				days = days + 1;
				temp.addDay();
			}
			return days;
		} else {
			Date temp = date1;
			while (!IsEqual(temp, date2)) {
				days++;
				temp.addDay();
			}
			return days;
		}
	} else {
		cout << "Датите са еднакви !" << endl;
		return 0;
	}
}

// връща разликата между две дати в месеци
int operator/(const Date &date1, const Date &date2) {
	if (!IsEqual(date1, date2)) {
		int months = 0;
		if (IsBigger(date1, date2)) {
			Date temp = date2; //копираме date2 в temp за да можем да работим с нея
			while (!IsBigger(temp, date1)) {
				months++;
				temp.addMonth(1);
			}
			if (IsEqual(temp, date1))
				return months;
			else
				return --months;
		} else {
			Date temp = date1;
			while (!IsBigger(temp, date2)) {
				months++;
				temp.addMonth(1);
			}
			if (IsEqual(temp, date2))
				return months;
			else
				return --months;
		}
	} else {
		cout << "Датите са еднакви !" << endl;
		return 0;
	}
}

// връща разликата между две дати в години
int operator|(const Date &date1, const Date &date2) {
	return (date1 / date2) / 12;
}

// връща разликата между две дати в седмици
int operator%(const Date &date1, const Date &date2) {
	return (date1 - date2) / 7;
}

//проверява дали дадената дата е почивен ден
bool Date::isHoliday() const {
	bool flag1 = false; // ако денят е празник с постоянна дата
	bool flag2 = false; // ако денят е Великден или Велики петък или Велика събота
	bool flag3 = false; // ако денят е събота или неделя
	for (int i = 0; i < 10; i++) {
		if (day == Holidays[i].getDay() && month == Holidays[i].getMonth()) {
			flag1 = true;
			break;
		}
	}
// проверяваме дали нашия ден съвпада с Великден или Велики петък или Велика събота
	if (IsEqual(*this, greatDay(year) + 1) || IsEqual(*this, greatDay(year))
			|| IsEqual(*this, greatDay(year) - 1)
			|| IsEqual(*this, greatDay(year) - 2))
		flag2 = true;
	if ((*this).getDayOfWeek() == NameOfDay[0]
			|| (*this).getDayOfWeek() == NameOfDay[6])
		flag3 = true;
	return flag1 || flag2 || flag3;
}

// определя кога е Великден в дадената година
Date greatDay(int _year) {
	int a = _year % 19;
	int b = _year % 4;
	int c = _year % 7;
	int d = (19 * a + 15) % 30;
	int e = (2 * b + 4 * c + 6 * d + 6) % 7;
	int theDay, theMonth;
	if (d + e > 10) {
		theDay = d + e - 9;
		theMonth = 4;
	} else {
		theDay = 22 + d + e;
		theMonth = 3;
	}
	Date GreatDay;
	Date temp(theDay, theMonth, _year);
	if (IsBigger(Date(1, 3, 2100), temp))
		GreatDay = temp + 13;
	else
		GreatDay = temp + 14;
	return GreatDay;
}

// проверява най-близкия работен ден в зависимост от параметъра p,
// ако p > 0 то търсим напред във времето
// ако p < 0 то търсим назад във времето
// ако p = 0 търсим без значение от посоката
Date Date::ClosestWorkDay(int p) const {
	if (p > 0)
		return ClosestWorkDayForward(*this);
	else if (p < 0)
		return ClosestWorkDayBack(*this);
	else {
		if (*this - ClosestWorkDayForward(*this)
				> *this - ClosestWorkDayBack(*this))
			return ClosestWorkDayBack(*this);
		else
			return ClosestWorkDayForward(*this);
	}
}

// намира най-близкия работен ден от някаква дата
Date Date::ClosestWorkDayForward(const Date &date) const {
	int days; // дните които ще прибавяме
	Date temp = date;
	temp = temp + 1;
	while (temp.isHoliday()) {
		temp = temp + 1;
		days++;
	}
	return temp;
}

// намира най-близкия работен ден
Date Date::ClosestWorkDayBack(const Date &date) const {
	int days;
	Date temp = date;
	temp = temp - 1;
	while (temp.isHoliday()) {
		temp = temp - 1;
		days++;
	}
	return temp;
}

// включва и изключва режим 2
void Date::ChangeMode2() {
	if (Mode2 == 0)
		cout
				<< "Режима на работа за нагласяне на най-близкия работен ден след промяна на датата е включен !"
				<< endl;
	else
		cout
				<< "Режима на работа за нагласяне на най-близкия работен ден след промяна на датата е изключен !"
				<< endl;
	Mode2 = !Mode2;
}

// режим на работа 1
void Date::ChangeMode1() {
	if (Mode1 == 0)
		cout << "Режима на работа с работни дни е включен!" << endl;
	else
		cout << "Режима на работа с работни дни е изключен !" << endl;
	Mode1 = !Mode1;
}

// оператор =
Date& Date::operator=(const Date &other) {
	Mode1 = other.Mode1;
	Mode2 = other.Mode2;
	day = other.day;
	month = other.month;
	year = other.year;
	return *this;
}

// режим на работа 2
Date& Date::ChangetoMode2() {
	cout << "Въведете параметър за търсене :" << endl;
	cout << "1) Въведете положително число за търсене напред във времето"
			<< endl
			<< "2) Въведете отрицателно число за търсене назад във времето"
			<< endl << "3) Въведете 0 за търсене без значение от посоката"
			<< endl;
	int p; // параметър определящ посоката на търсене
	cin >> p;
	if (!cin) {
		cout << "Некоректни данни!" << endl;
		exit(1);
	}
	*this = this->ClosestWorkDay(p);
	this->Mode2 = 1;
	return *this;
}

