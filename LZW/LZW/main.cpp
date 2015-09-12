#include <stdio.h>
#include <iostream>
#include "Dictionary.cpp"
#include <fstream>
#include "fileManager.cpp"
//#include "dictionaryItem.cpp"

int main()
{
	//LzwDictionary dictionary;;

	//dictionaryItem* di = dictionary.search(nullptr, 255);

	fileManager fm = fileManager("M:/Google Drive/Programming/Visual C++/LZW/LZW/LZW/Debug/test_document.txt");

	while (true)
	{
		uint8_t byte = fm.getByte();

		if (fm.endOfFile())
		{
			break;
		}

		std::cout << byte;
	}

	return 0;
}