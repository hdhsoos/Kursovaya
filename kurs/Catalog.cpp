#include "Catalog.h"
#include "File.h"
#include "File.cpp"

Catalog::Catalog(int a_nameOfCatalog)
{
	numberOfCatalog = a_nameOfCatalog;
	for (int i{ 1 }; i < size; i++) {
		filesList[i].setNextIndex(i+1);
	}
	countOfFiles = 0;
}

Catalog::Catalog() : Catalog(-1) {}


bool Catalog::isEmpty()
{
	return (countOfFiles == 0);
}

bool Catalog::isFull()
{
	return (countOfFiles == size - 1);
}

bool Catalog::show()
{
	if (isEmpty()) {
		std::cout << "\n\tКаталог " << numberOfCatalog << ": Пусто.";
		return false;
	}
	else {
		std::cout << "\n\tКаталог " << numberOfCatalog << ":" << std::endl;
		for (int i=0; i < countOfFiles; i++) {
			if (filesList[i].getFileNumber() == -1) {
				break;
			}
			std::cout << "\t" << filesList[i].getFileNumber() << " - " << filesList[i].getSize() << " Мб" << std::endl;
		}
		return true;
	}
}

bool Catalog::searchFile(int number)
{

	int temp{ filesList[0].getNextIndex() };
	while (temp != 0) {
		if (filesList[temp].getFileNumber() == number) {
			return true;
		}
		temp = filesList[temp].getNextIndex();
	}
	return false;
}

int Catalog::getNumberOfCatalog()
{
	return numberOfCatalog;
}

void Catalog::setNumberOfCatalog(int a_nameOfCatalog)
{
	numberOfCatalog = a_nameOfCatalog;
}

void Catalog::writeToFile(std::ofstream& file, std::string separator, std::string end)
{
	if (isEmpty()) {
		return;
	}
	else {
		for (int i = 0; i < countOfFiles; i++) {
			if (filesList[i].getFileNumber() == -1) {
				break;
			}
			file << filesList[i].getFileNumber() << "\n";
			file << filesList[i].getSize() << "\n";
		}
		return;
	}
}



bool Catalog::addFile(int newFileNumber, int newFileSize)
{
	if (isFull()) {
		return false;
	}
	if (isEmpty()) {
		filesList[0].setFileNumber(newFileNumber);
		filesList[0].setSize(newFileSize);
		countOfFiles++;
		return true;
	}
	else {
		int i{ 0 };
		for (i; i < countOfFiles; i++) {
			if (filesList[i].getFileNumber() > newFileNumber) {
				for (int j = countOfFiles; j > i; j--) {
					filesList[j].setFileNumber(filesList[j - 1].getFileNumber());
					filesList[j].setSize(filesList[j - 1].getSize());
				}
				filesList[i].setFileNumber(newFileNumber);
				filesList[i].setSize(newFileSize);
				break;
			}
		}
		if (i == countOfFiles) {
			filesList[i].setFileNumber(newFileNumber);
			filesList[i].setSize(newFileSize);
		}
		countOfFiles++;
		return true;
	}
	return false;
}


bool Catalog::deleteFile(int fileNumber)
{

	bool f(false);
	int fileToDeleteIndex=-1;
	for (int i = 0; i < countOfFiles; i++) {
		if (filesList[i].getFileNumber() == -1) {
			break;
		}
		if (filesList[i].getFileNumber() == fileNumber) {
			fileToDeleteIndex = i;
			break;
		}
	}
	if (fileToDeleteIndex == -1){
		return false;
	}
	else {
		for (int j = fileToDeleteIndex; j < countOfFiles; j++) {
			filesList[j].setFileNumber(filesList[j+1].getFileNumber());
			filesList[j].setSize(filesList[j+1].getSize());
		}
		filesList[countOfFiles].setFileNumber(-1);
		filesList[countOfFiles].setSize(-1);
		countOfFiles--;
		return true;
	}

}

Catalog::~Catalog()
{
	for (int i = 0; i < countOfFiles; i++) {
		filesList[i].~File();
	}
	filesList[0].setNextIndex(0);
	countOfFiles = 0;
	numberOfCatalog = -1;
}