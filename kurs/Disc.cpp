#include "Disc.h"
#include "Catalog.h"
#include "Catalog.cpp"

Disc::Disc(const std::string& a_name) {
	name = a_name;
	countOfCatalogs = 0;
	first = last = -1;
}

Disc::Disc() : Disc("None") {}


const std::string& Disc::getName()
{
	return name;
}

void Disc::setName(const std::string& a_name)
{
	name = a_name;
}

bool Disc::isFull()
{
	return countOfCatalogs == size;
}

bool Disc::isEmpty()
{
	return countOfCatalogs == 0;
}

bool Disc::addCatalog(int number)
{
	if (isFull()) {
		return false;
	}

	if (last == size - 1) {
		last = 0;
		catalogsQueue[last].setNumberOfCatalog(number);
	}
	else {
		if (isEmpty()) {
			first = 0;
		}
		last++;
		catalogsQueue[last].setNumberOfCatalog(number);
	}
	countOfCatalogs++;
	return true;
}

bool Disc::deleteCatalog()
{
	if (isEmpty()) {
		return false;
	}
	else if (first == last) { //всего 1 элемент
		catalogsQueue[first].~Catalog();
		first = -1;
		last = -1;
	}
	else if (first == size - 1) {
		catalogsQueue[first].~Catalog();
		first = 0;
	}
	else {
		catalogsQueue[first].~Catalog();
		first++;
	}
	countOfCatalogs--;
	return true;
}

bool Disc::addFile(int newFileName, int newFileSize)
{
	if (!catalogsQueue[last].addFile(newFileName, newFileSize)) {
		return false;
	}
	return true;
}


bool Disc::deleteFileInLast(int fileNumber)
{
	return catalogsQueue[last].deleteFile(fileNumber);
}

bool Disc::searchFileInLast(int fileNumber)
{
	return catalogsQueue[last].searchFile(fileNumber);
}

bool Disc::catalogIsEmpty()
{
	return catalogsQueue[last].isEmpty();
}

bool Disc::catalogIsFull()
{
	return catalogsQueue[last].isFull();
}

bool Disc::writeToFile(const std::string fileName, std::string separator, std::string end)
{
	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Файл не был открыт!" << std::endl;
		return false;
	}

	file << name + "\n";
	if (isEmpty()) {
		file << end << "\n";
		file.close();
		std::cout << "Текущий диск записан в файл " << '"' << fileName << '"' << "!" << std::endl;
		return true;
	}
	else {
		file << separator << "\n";
	}

	while (!isEmpty()) {
		file << catalogsQueue[first].getNumberOfCatalog(); 
		file << "\n";
		catalogsQueue[first].writeToFile(file, separator, end);
		deleteCatalog();
		if (!isEmpty()) {
			file << separator << "\n";
		}
	}
	file << end << "\n";
	file.close();
	std::cout << "Текущий диск записан в файл " << '"' << fileName << '"' << "!" << std::endl;
	name = "None";
	return true;
}

bool Disc::show()
{
	if (isEmpty()) {
		std::cout << "Диск " << name << ":" << std::endl;
		std::cout << "\tКаталогов нет" << std::endl;
		return false;
	}

	std::cout << "Диск " << name << ":";

	if (last >= first) {
		for (int i{ first }; i <= last; i++) {
			catalogsQueue[i].show();
		}
		std::cout << std::endl;
	}
	else {
		for (int i{ first }; i < size; i++) {
			catalogsQueue[i].show();
		}
		for (int i{ 0 }; i <= last; i++) {
			catalogsQueue[i].show();
		}
		std::cout << std::endl;
	}
}

Disc::~Disc()
{
	while (!isEmpty()) {
		deleteCatalog();
	}
	name = "None";
}
