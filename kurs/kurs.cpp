#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <windows.h> 
#include "Disc.h"
#include "Disc.cpp"
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>


namespace constants {
	const int catalogNumberMin{ 1 };
	const int catalogNumberMax{ 99 };
	const int fileNumberMin{ 1 };
	const int fileNumberMax{ 999 };
	const int sizeMin{ 1 };
	const int sizeMax{ 99 };

	const std::string separator{ "Catalog" };
	const std::string end{ "stop" };
}

namespace errors {
	const int impossibleNumber{ -1 };
	const std::string voidString{ "" };
	const std::string errorString{ "0" };
}


Disc* disc = NULL;


int failure() {
	int a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Ошибка ввода. Повторите: ";
	}
	return a;
}

int getNumber(int min = INT_MIN, int max = INT_MAX) {

	bool error{ false };
	while (true) {
		std::cout << "-> ";
		std::string string{};
		std::cin >> string;

		int number;
		try {
			number = std::stoi(string);
			error = false;
		}
		catch (std::invalid_argument iaException) {
			std::cout << "Введенные данные не были приняты: введите число!" << std::endl;
			error = true;
		}
		catch (std::out_of_range oorException) {
			error = true;
			std::cout << "Введенные данные не были приняты: введите чиcло в правильном диапазоне!" << std::endl;
		}
		if (!error)
		{
			if ((number <= max) && (number >= min)) {
				return number;
			}
			else {
				std::cout << "Введенные данные не были приняты: введите чиcло в правильном диапазоне!" << std::endl;
			}
		}
	}
}

int getNumberFromFile(std::ifstream& file, int min = INT_MIN, int max = INT_MAX) {

	std::string string{};
	file >> string;
	int number;

	try {
		number = std::stoi(string);
	}
	catch (std::invalid_argument iaException) {
		if (string == constants::end) {
			return -2;
		}
		if (string == constants::separator) {
			return -3;
		}
		return errors::impossibleNumber;
	}
	catch (std::out_of_range oorException) {
		return errors::impossibleNumber;
	}

	if ((number <= max) && (number >= min)) {
		return number;
	}
	else {
		return errors::impossibleNumber;
	}
}

std::string getString() {
	std::string string{};
	bool l{ true };
	while (l) {
		l = false;
		std::cout << "-> ";
		std::cin >> string;
		for (char c : string) {
			if (!isalpha(c) || !isascii(c)) {
				std::cout << "Ошибка! Используйте только латинский алфавит." << std::endl;
				l = true;
				
			}
		}
	}
	return string;
}

std::string getStringFromFile(std::ifstream& file) {
	std::string string;
	file >> string;
	if (string == "") {
		return errors::voidString;
	}
	for (char c : string) {
		if (!isalpha(c) || !isascii(c)) {
			return errors::errorString;
		}
	}
	return string;
}

bool getAndCheckStringFromFile(std::ifstream& file, std::string& string) {
	string = getStringFromFile(file);
	if (string == constants::end) {
		std::cout << "Чтение файла завершено!" << std::endl;
		return false;
	}
	else if (string == errors::voidString) {
		std::cout << "Ошибка при чтении файла: была получена пустая строка!" << std::endl;
		return false;
	}
	else if (string == errors::errorString) {
		std::cout << "Ошибка при чтении файла: использовались недопустимые символы в строке!" << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool getAndCheckNumberFromFile(std::ifstream& file, int& number, int min = INT_MIN, int max = INT_MAX) {
	number = getNumberFromFile(file, min, max);
	if (number == errors::impossibleNumber) {
		return false;
	}
	else if (number == -2) {
		return false;
	}
	else if (number == -3) {
		return false;
	}
	else {
		return true;
	}
}



void readDiscFromFile(Disc& i_disc, std::string fileName) {
	Disc disc;
	if (!i_disc.isEmpty()) {
		std::cout << "При загрузке из файла существующий факультет будет очищен: " << std::endl;
		std::cout << "\t1 - Отмена" << std::endl;
		std::cout << "\t2 - Выполнить загрузку" << std::endl;
		int choice{ getNumber(1, 2) };
		if (choice == 1) {
			return;
		}
		else {
			i_disc.~Disc();
			disc = Disc();
		}
	}

	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Файл не был открыт!" << std::endl;
		return;
	}

	std::string newDataFromFile;
	if (getAndCheckStringFromFile(file, newDataFromFile)) {
		disc.setName(newDataFromFile);
	}
	else {
		file.close();
		return;
	}

	if (!getAndCheckStringFromFile(file, newDataFromFile)) {
		file.close(); return;
	}  // проверка строки после названия 
	if (!(newDataFromFile == constants::separator)) {
		std::cout << "Ошибка чтения файла: ошибка в первой или второй строке!" << std::endl;
		file.close();
		return;
	}

	while (true) {
		int newCatalogNumberFromFile;
		if (!getAndCheckNumberFromFile(file, newCatalogNumberFromFile, constants::catalogNumberMin, constants::catalogNumberMax)) {
			file.close();
			return;
		}

		if (!disc.addCatalog(newCatalogNumberFromFile)) {
			std::cout << "Ошибка чтения файла: зданий больше, чем вмещает диск! " << std::endl;
			file.close();
			return;
		}

		int prevFileNumber{};

		while (true) {

			int newFileName;
			if (!getAndCheckNumberFromFile(file, newFileName, constants::fileNumberMin, constants::fileNumberMax)) {
				if (newFileName == -2) { //если строка end
					i_disc = disc;
					file.close();
					return;
				}
				else if (newFileName == -3) { //если строка separator
					break;
				}
				else {
					file.close();
					return;
				}
			}



			if (disc.catalogIsFull()) {
				std::cout << "Ошибка чтения файла: аудиторий больше, чем вмещает здание!" << std::endl;
				file.close();
				return;
			}

			int newSize{};
			if (!getAndCheckNumberFromFile(file, newSize, constants::sizeMin, constants::sizeMax)) {
				file.close();
				return;
			}
			disc.addFile(newFileName, newSize);

			prevFileNumber = newFileName;
		}
	}
}



void writeDiscToFile(Disc& disc, std::string fileName) {
	disc.writeToFile(fileName, constants::separator, constants::end);
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	Disc disc;
	while (true) {
		disc.show();
		std::cout << "\n Выберите действие:\n";
		std::cout << " 1. Добавить каталог\n";
		std::cout << " 2. Добавить файл\n";
		std::cout << " 3. Удалить каталог\n";
		std::cout << " 4. Удалить файл\n";
		std::cout << " 5. Изменить название диска\n";
		std::cout << " 6. Загрузить из файла\n";
		std::cout << " 7. Выгрузить в файл\n";
		std::cout << " 0. Выход\n";
		n = failure();
		if (n == 1) {
			if (disc.isFull()) {
				std::cout << "Диск переполнен!" << std::endl;
			}
			else {
				std::cout << "Введите номер нового каталога: \n";
				disc.addCatalog(getNumber(constants::catalogNumberMin, constants::catalogNumberMax));
				std::cout << "Каталог был добавлен!" << std::endl;
			}
		}
		else if (n == 2)
		{
			if (disc.isEmpty()) {
				std::cout << "Добавление невозможно: добавьте каталог для добавления в него файла!" << std::endl;
			}
			else {
				std::cout << "Введите номер файла: " << std::endl;
				int newFileName{ getNumber(constants::fileNumberMin, constants::fileNumberMax) };
				std::cout << "Введите размер файла: " << std::endl;
				int newFileSize{ getNumber(constants::sizeMin, constants::sizeMax) };
				disc.addFile(newFileName, newFileSize);
			}
			
		}
		else if (n == 3)
		{
			if (disc.isEmpty()) {
				std::cout << "Удаление невозможно: диск пуст!" << std::endl;
			}
			else {
				disc.deleteCatalog();
				std::cout << "Каталог был удалён!" << std::endl;
			}
			
		}
		else if (n == 4)
		{
			if (disc.isEmpty()) {
				std::cout << "Невозможно удалить файл: нет каталогов!" << std::endl;
			}
			else if (disc.catalogIsEmpty()) {
				std::cout << "Невозможно удалить файл: нет файлов в последнем каталоге!" << std::endl;
			}
			else {
				std::cout << "Введите номер файла: " << std::endl;
				int fileNumber{ getNumber(constants::fileNumberMin, constants::fileNumberMax) };
				if (!disc.deleteFileInLast(fileNumber)) {
					std::cout << "Такого файла в последнем каталоге не найдено!" << std::endl;
				}
				std::cout << "Удаление завершено" << std::endl;
			}
		}
		else if (n == 5)
		{
			std::cout << "Введите название диска: " << std::endl;
			disc.setName(getString());
			
		}
		else if (n == 6)
		{
			readDiscFromFile(disc, "file_disc.txt");
			
		}
		else if (n == 7)
		{
			writeDiscToFile(disc, "file_disc.txt");
			
		}
		else if (n == 0) {
			break;
		}
		else{
			std::cout << "Ошибка ввода." << std::endl;
		}
		std::cout << "\n" << std::endl;
	}
}
