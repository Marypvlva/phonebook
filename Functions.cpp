#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <limits>
#include <list>

#include "Object.h"


#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
using namespace std;


bool Person::read(istream &is, bool flag) {
	string temp;
	bool good = true;

	if (flag)
		cout << "������� ������ ���: ";
	getline(is, fullName);
	int cnt = 0; for (int i = 0; i < fullName.size(); i++) if (fullName[i] == ' ')cnt++;
	if (cnt != 2) good = false;

	if (flag)
		cout << "������� ���� ��������: ";
	getline(is, temp);
	try
	{
		birthDay = stoi(temp);
	}
	catch (...)
	{
		good = false;
	}

	if (flag)
		cout << "������� ����� ��������: ";
	getline(is, temp);
	try
	{
		birthMonth = stoi(temp);
	}
	catch (...)
	{
		good = false;
	}

	if (flag)
		cout << "������� ��� ��������: ";
	getline(is, temp);
	try
	{
		birthYear = stoi(temp);
	}
	catch (...)
	{
		good = false;
	}
	//is.ignore(numeric_limits<streamsize>::max(), '\n');
	if (flag)
		cout << "������� ����� ��������: ";
	getline(is, phoneNumber);


	vector<int> one = { 1,3,5,7,8,10,12 }, two = { 2 }, three = { 4,6,9,11 };
	if (std::find(one.begin(), one.end(), birthMonth) != one.end())
	{
		if (birthDay < 1 || birthDay > 31) good = false;
	}
	else if (std::find(two.begin(), two.end(), birthMonth) != two.end())
	{
		if (birthDay % 4 == 0)
		{
			if (birthMonth % 100 == 0)
			{
				if (birthMonth % 400 == 0)
				{
					if (birthDay < 1 || birthDay > 29) good = false;
				}
				else
				{
					if (birthDay < 1 || birthDay > 28) good = false;
				}
			}
			else
			{
				if (birthDay < 1 || birthDay > 29) good = false;

			}
		}
		else
		{
			if (birthDay < 1 || birthDay > 28) good = false;
		}
	}
	else if (std::find(three.begin(), three.end(), birthMonth) != three.end())
	{
		if (birthDay < 1 || birthDay > 30) good = false;
	}
	else
	{
		good = false;
	}

	return good;
}

void Person::write() const {
	cout << "������ ���: " << fullName << "\n";
	cout << "���� ��������: " << birthDay << "/" << birthMonth << "/" << birthYear << "\n";
	cout << "����� ��������: " << phoneNumber << "\n";
}

int Person::compare(const Person &other) const {
	int nameComp = fullName.compare(other.fullName);
	if (nameComp != 0) return nameComp;
	if (birthYear != other.birthYear) return birthYear - other.birthYear;
	if (birthMonth != other.birthMonth) return birthMonth - other.birthMonth;
	return birthDay - other.birthDay;
}

bool Person::check(const string &nameCond, const string &dayCond, const string &monthCond,
	const string &yearCond, const string &phoneCond) const {
	if (nameCond != "*" && nameCond != fullName) return false;
	if (dayCond != "*" && stoi(dayCond) != birthDay) return false;
	if (monthCond != "*" && stoi(monthCond) != birthMonth) return false;
	if (yearCond != "*" && stoi(yearCond) != birthYear) return false;
	if (phoneCond != "*" && phoneCond != phoneNumber) return false;
	return true;
}
int Person::daysBeforeBirthday() const {
	time_t now = time(0);
	tm *ltm = localtime(&now);

	int currentYear = 1900 + ltm->tm_year;
	int currentMonth = 1 + ltm->tm_mon;

	int currentDay = ltm->tm_mday;

	int nextBirthYear = currentYear;
	if (currentMonth > birthMonth || (currentMonth == birthMonth && currentDay > birthDay)) {
		nextBirthYear++;
	}

	tm birthday = {};
	birthday.tm_mday = birthDay;
	birthday.tm_mon = birthMonth - 1;
	birthday.tm_year = nextBirthYear - 1900;

	time_t nextBirthdayTime = mktime(&birthday);
	double seconds = difftime(nextBirthdayTime, now);
	return static_cast<int>(seconds / (60 * 60 * 24));
}

bool Person::operator<(const Person& other) const {
	return compare(other) < 0;
}

bool Person::operator>(const Person& other) const {
	return compare(other) > 0;
}

bool Person::operator<=(const Person& other) const {
	return compare(other) <= 0;
}

bool Person::operator>=(const Person& other) const {
	return compare(other) >= 0;
}
void Person::writeFile(ostream& file) {
	file << fullName << " " << birthDay << " " << birthMonth << " " << birthYear << " " << phoneNumber << endl;
}
bool Person::readFile(ifstream& is) {
	string a, b, c;
	if (!(is >> a >> b >> c >> birthDay >> birthMonth >> birthYear >> phoneNumber)) {
		return false;
	}
	fullName = a + " " + b + " " + c;
	return true;
}



void PhoneBook::clear() {
	book.clear();
};
void PhoneBook::add(const Person& p) {
	book.push_back(p);
}
void PhoneBook::sort() {
	book.sort();
}
void PhoneBook::addToSorted(Person& p) {
	auto ptr = book.begin();
	while (ptr != book.end() && (*ptr) < p) ptr++;
	book.insert(ptr, p);
}
void PhoneBook::operator<<(ofstream& of) {
	for (auto i = book.begin(); i != book.end(); i++) {
		i->writeFile(of);
	}
}
void PhoneBook::operator>>(ifstream& is) {
	Person p;
	while (p.readFile(is)) {
		addToSorted(p);
	}
}
void PhoneBook::getBirthday() {
	int minDays = 10000000;//numeric_limits<int>::max();
	auto current = book.begin();
	auto closest = book.end();
	while (current != book.end()) {
		int days = (*current).daysBeforeBirthday();
		if (days < minDays) {
			minDays = days;
			closest = current;
		}
		current++;
	}
	if (closest != book.end())
	{
		cout << "��������� ���� �������� �: ";
		closest->write();
		cout << "���� �� ���������� ��� ��������: " << minDays << endl;
	}
	else
	{
		cout << "������ ���� ����\n";
	}
}

void PhoneBook::remove(const string &nameCond, const string &dayCond, const string &monthCond,
	const string &yearCond, const string &phoneCon) {
	auto tmp = book.begin();
	while (tmp != book.end()) {
		if (tmp->check(nameCond, dayCond, monthCond, yearCond, phoneCon)) {
			tmp = book.erase(tmp);
		}
		else {
			++tmp;
		}
	}
}
void PhoneBook::write(const string &nameCond, const string &dayCond, const string &monthCond,
	const string &yearCond, const string &phoneCon) {
	for (auto i = book.begin(); i != book.end(); i++) {
		if (i->check(nameCond, dayCond, monthCond, yearCond, phoneCon)) {
			i->write();
		}
	}
}
