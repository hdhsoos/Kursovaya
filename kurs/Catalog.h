#pragma once
#include "File.h"
#include <iostream>
#include <iomanip>
#include <fstream>

class Catalog
{
private:
	int numberOfCatalog;

	static const int size{ 5 };
	File filesList[size];
	int countOfFiles;
public:
	Catalog();
	Catalog(int a_nameOfCatalogs);

	bool isEmpty();
	bool isFull();

	bool show();
	bool searchFile(int number);

	int getNumberOfCatalog();
	void setNumberOfCatalog(int a_nameOfCatalog);

	void writeToFile(std::ofstream& file, std::string separator, std::string end);
	bool addFile(int newFileNumber, int newFileSize);
	bool deleteFile(int fileNumber);



	~Catalog();
};