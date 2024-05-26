#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <limits>
#include <list>

using namespace std;

class Person {
public:
	string fullName;
	int birthDay;
	int birthMonth;
	int birthYear;
	string phoneNumber;

	Person() : fullName(""), birthDay(1), birthMonth(1), birthYear(1900), phoneNumber("") {}
	Person(string fullName, int day, int month, int year, string phoneNumber)
		: fullName(fullName), birthDay(day), birthMonth(month), birthYear(year), phoneNumber(phoneNumber) {}

	bool read(istream &is = cin, bool flag = true);


	void write() const;

	int compare(const Person &other) const;

	bool check(const string &nameCond, const string &dayCond, const string &monthCond,
		const string &yearCond, const string &phoneCond) const;
	int daysBeforeBirthday() const;

	bool operator<(const Person& other) const;

	bool operator>(const Person& other) const;

	bool operator<=(const Person& other) const;

	bool operator>=(const Person& other) const;
	void writeFile(ostream& file);
	bool readFile(ifstream& is);
};

class PhoneBook {
private:
	list <Person> book;
public:
	void clear();
	void add(const Person& p);
	void sort();
	void addToSorted(Person& p);
	void operator<<(ofstream& of);
	void operator>>(ifstream& is);
	void getBirthday();

	void remove(const string &nameCond, const string &dayCond, const string &monthCond,
		const string &yearCond, const string &phoneCon);
	void write(const string &nameCond, const string &dayCond, const string &monthCond,
		const string &yearCond, const string &phoneCon);

};
