#pragma once
#include "Catalog.h"
class Disc
{
private:
	std::string name;

	static const int size{ 5 };
	Catalog catalogsQueue[size];
	int countOfCatalogs;

	int first;
	int last;

public:

	Disc();
	Disc(const std::string& a_name);

	const std::string& getName();
	void setName(const std::string& a_name);

	//методы для работы с очередью 
	bool isFull();
	bool isEmpty();

	bool addCatalog(int number); //добавление в конец
	bool deleteCatalog(); //удаление первого

	//методы для работы с последним добавленным в очередь списком 
	bool addFile(int newFileNumber, int newFileCountOfPlaces);
	bool deleteFileInLast(int fileNumber);
	bool searchFileInLast(int fileNumber);
	bool catalogIsEmpty();
	bool catalogIsFull();


	bool writeToFile(const std::string fileName, std::string separator, std::string end);
	bool show();

	~Disc();
};