/*
 * Date.h
 *
 *  Created on: May 18, 2015
 *      Author: zyapkov
 */

#ifndef DATE_H_
#define DATE_H_

class Date {
	friend std::ostream& operator<<(std::ostream& out, Date const &date); // извежда дата
	friend std::istream& operator>>(std::istream& in, Date &date); // въвежда дата
	friend Date operator+=(Date &date, int _days); // добавя към дата _days на брой дни
	friend Date operator-=(Date &date, int _days); // преминава на _days дни по-назад от датата
	friend Date operator*=(Date &date, int _months); // преминава с _months на брой месеца по-напред от датата
	friend Date operator/=(Date &date, int _months); // преминава с _months на брой месеца по-назад от датата
	friend Date operator&=(Date &date, int _years); // добавя _years на брой години към текущата дата
	friend Date operator|=(Date &date, int _years); // изважда _years на брой години от текущата дата
	friend Date operator^=(Date &date, int weeks); // добавя weeks на брой седмици към текущата дата
	friend Date operator%=(Date &date, int weeks); // изважда weeks на брой седмици от текущата дата
	friend int operator-(const Date &date1, const Date &date2); // намира разликата между две дати в дни
	friend int operator/(const Date &date1, const Date &date2); // намира разликата между две дати в месеци
	friend int operator|(const Date &date1, const Date &date2); // намира разликата между две дати в години
	friend int operator%(const Date &date1, const Date &date2); // намира разликата между две дати в седмици
	friend bool IsBigger(const Date &date1, const Date &date2); // проверява дали date1 е по-голяма или равна на date2
	friend bool IsEqual(const Date &date1, const Date &date2); // проверява дали date1 е същата като date2
public:
	Date(int = 1, int = 1, int = 2015); // конструктор с подразбиращи се стойности
	Date(const Date&); // copy конструктор
	Date& operator=(const Date&);
	int getDay() const; // селектор за ден
	int getMonth() const; // селектор за месец
	int getYear() const; // селектор за година
	int WeeksToDays(int weeks) const; // преобразува weeks седмици в дни и връща дни като резултат
	bool leapYear(int) const; // проверява дали годината е високосна
	bool StartOfMonth(int) const; // проверява за начало на месец
	bool EndOfMonth(int _month) const; //проверява за край на месец
	bool FirstMonth() const; // проверява за начало на година(първи месец)
	bool LastMonth() const; // проверява за край на година(последен месец)
	const char* getDayOfWeek() const; // връща името на деня от седмицата
	void setDate(int, int, int); // мутатор за дата
	void setDay(int); // мутатор за ден
	void setMonth(int); // мутатор за месец
	void setYear(int); // мутатор за година
	// аритметични операции с дати :
	Date& operator+(int _days); // добавя към дата _days на брой дни
	Date& operator++(); // преминава с един ден напред от датата ++date
	Date operator++(int unused); // преминава с един ден напред от датата date++
	Date& operator-(int _days); // преминава на _days дни по-назад от датата
	Date& operator--(); // преминава един ден по-назад от датата --date
	Date operator--(int unused); // преминава един ден по-назад от датата date--
	Date& operator*(int _months); // преминава с _months на брой месеца по-напред от датата
	Date& operator/(int _months); // преминава с _months на брой месеца по-назад от датата
	Date& operator&(int _years); // добавя _years на брой години към текущата дата
	Date& operator|(int _years); // изважда _years на брой години от текущата дата
	Date& operator^(int weeks); // добавя weeks на брой седмици към текущата дата
	Date& operator%(int weeks); //премахва weeks на брой седмици от текущата дата
	bool isHoliday() const; // определя дали даден ден е почивен
	Date ClosestWorkDay(int) const; // намира най-близкия работен ден
	Date ClosestWorkDayForward(const Date&) const; // намира най-близкия работен ден напред във времето
	Date ClosestWorkDayBack(const Date&) const; // намира най-близкия работен ден назад във времето
	void ChangeMode2(); // включва и изключва режим 2
	void ChangeMode1(); // включва и изключва режим 1
	Date& ChangetoMode2(); // превключва на режим 2
private:
	int day, month, year; // ден, месец, година
	void addDay(); // функция, която преминава на следващия ден
	void remDay(); // функция, която преминава на предишния ден
	void addMonth(int); // функция, която преминава на следващия месец
	void remMonth(int); // функция, която преминава на предишния месец
	void addYear(int); //функция, преминава на следваща година
	void remYear(int); //функция, която преминава на предходна година
	// променя режима на работа на всички оператори, така че ако резултата е почивен ден
	// да се наглася да бъде най-близкия работен ден
	bool Mode2;
	//променя режима на работа така че да смята с работни дни
	bool Mode1;
};

Date greatDay(int); // определя кога е Великден в подадена като параметър година

#endif /* DATE_H_ */
