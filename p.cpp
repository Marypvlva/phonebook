// p.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Object.h"

using namespace std;
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS


int main()
{
	setlocale(LC_ALL, "Russian");
	PhoneBook book;
	string command;

	cout << "Приложение 'Телефонная книга'. Наберите 'help' для получения справки." << std::endl;

	while (true) {
		cout << "> ";
		getline(cin, command);
		if (command == "help") {
			cout << "Доступные команды:\n"
				<< "  help - Показать это справочное сообщение\n"
				<< "  clear - Очистить телефонную книгу\n"
				<< "  load <filename> - Загрузить телефонную книгу из файла\n"
				<< "  save <filename> - Сохранить телефонную книгу в файл\n"
				<< "  add - Добавить нового человека в телефонную книгу\n"
				<< "  sort - Сортировать телефонную книгу\n"
				<< "  find <name> <day> <month> <year> <phone> - Найти и показать людей, соответствующих условиям\n"
				<< "  delete <name> <day> <month> <year> <phone> - Удалить людей, соответствующих условиям\n"
				<< "  exit - Выйти из приложения\n"
				<< "  birthday - Показать следующего человека, у которого будет день рождения\n";
		}
		else if (command == "clear") {
			book.clear();
		}
		else if (command.substr(0, 4) == "load") {
			string filename;
			try {
				filename = command.substr(5);
			}
			catch (...)
			{
				cout << "Неизвестная команда: " << command << std::endl;
			}

			ifstream file(filename);
			if (file) {
				book >> file;
				cout << "Загружено из " << filename << endl;
				file.close();
			}
			else {
				cout << "Не удалось открыть " << filename << endl;
			}
		}
		else if (command.substr(0, 4) == "save") {
			string filename;
			try {
				filename = command.substr(5);
			}
			catch (...)
			{
				cout << "Неизвестная команда: " << command << std::endl;
			}

			ofstream file(filename);
			if (file) {
				book << file;
				cout << "Сохранено в " << filename << endl;
			}
			else {
				cout << "Не удалось открыть " << filename << endl;
			}
		}
		else if (command == "add") {
			Person p;
			if(p.read())
			book.add(p);
			else cout << "Данные введены некорректно\n";
		}
		else if (command == "sort") {
			book.sort();
		}
		else if (command.substr(0, 4) == "find") {
			try
			{
				istringstream iss(command.substr(5));
				string name, day, month, year, phone;
				string a, b, c;
				iss >> a;
				if (a == "*")
					iss >> day >> month >> year >> phone;
				else iss >> b >> c >> day >> month >> year >> phone;
				if (a == "*") name = "*";
				else name = a + " " + b + " " + c;
				book.write(name, day, month, year, phone);
			}
			catch (...)
			{
				
					cout << "Данные введены некорректно! "  << std::endl;
				
			}
		}
		else if (command.substr(0, 6) == "delete") {
			try
			{

				istringstream iss(command.substr(7));
				string name, day, month, year, phone;
				iss >> name >> day >> month >> year >> phone;
				book.remove(name, day, month, year, phone);
			}
			catch (...)
			{
				cout << "Данные введены некорректно! " << std::endl;

			}
		}
		else if (command == "exit") {
			break;
		}
		else if (command == "birthday") {
			book.getBirthday();
		}
		else {
			cout << "Неизвестная команда: " << command << std::endl;
		}
	}

	return 0;
}
