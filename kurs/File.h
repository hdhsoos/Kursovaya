#pragma once
class File
{
private:
	int numberOfFile;
	int size;
	int nextIndex;
public:
	File();
	File(int a_number, int a_size);

	int getFileNumber();
	void setFileNumber(int a_number);

	int getSize();
	void setSize(int a_size);

	int getNextIndex();
	void setNextIndex(int a_nextIndex);

	~File();
};