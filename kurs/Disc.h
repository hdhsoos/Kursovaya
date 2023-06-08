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

	//������ ��� ������ � �������� 
	bool isFull();
	bool isEmpty();

	bool addCatalog(int number); //���������� � �����
	bool deleteCatalog(); //�������� �������

	//������ ��� ������ � ��������� ����������� � ������� ������� 
	bool addFile(int newFileNumber, int newFileCountOfPlaces);
	bool deleteFileInLast(int fileNumber);
	bool searchFileInLast(int fileNumber);
	bool catalogIsEmpty();
	bool catalogIsFull();


	bool writeToFile(const std::string fileName, std::string separator, std::string end);
	bool show();

	~Disc();
};