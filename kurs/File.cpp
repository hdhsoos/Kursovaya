#include "File.h"


File::File(int a_number, int a_size) {
	numberOfFile = a_number;
	size = a_size;
	nextIndex = 0;
}

int File::getFileNumber()
{
	return numberOfFile;
}

void File::setFileNumber(int a_number)
{
	numberOfFile = a_number;
}

int File::getSize()
{
	return size;
}

void File::setSize(int a_size)
{
	size = a_size;
}

int File::getNextIndex()
{
	return nextIndex;
}

void File::setNextIndex(int a_nextIndex)
{
	nextIndex = a_nextIndex;
}

File::File() {
	numberOfFile = -1;
	size = -1;
	nextIndex = 0;
}



File::~File() {
	numberOfFile = -1;
	size = -1;
	nextIndex = -1;
}