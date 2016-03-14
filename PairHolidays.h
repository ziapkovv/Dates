/*
 * Pair.h
 *
 *  Created on: May 24, 2015
 *      Author: zyapkov
 */

// реализира двойка ден-месец

#ifndef PAIRHOLIDAYS_H_
#define PAIRHOLIDAYS_H_

class PairHolidays {
public:
	PairHolidays(int = 1, int = 1);
	void setPair(int, int);
	void print() const;
	int getDay()const;
	int getMonth()const;
	PairHolidays& operator-(int _days);
private:
	int month, day;
};

#endif /* PAIR_H_ */
