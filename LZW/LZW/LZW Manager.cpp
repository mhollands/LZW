#include <stdio.h>
#include <iostream>
#include "Dictionary.cpp"
#include <fstream>
#include "fileManager.cpp"

class LzwManager
{
public:
	void compress(char* file)
	{
		long byteCount = 0;
		long kByteCount = 0;
		LzwDictionary dictionary;

		fileManager fm = fileManager(file);

		dictionaryItem* currentitem = nullptr;
		int16_t currentItemCode;
		while (true)
		{
			uint8_t byte = fm.readByte();

			dictionaryItem* result = dictionary.search(currentitem, byte);

			if (result == nullptr)
			{
				fm.writeCode(currentItemCode);
				dictionary.addCode(currentitem, byte);
				currentitem = dictionary.search(nullptr, byte);
			}
			else
			{
				currentitem = result;
			}

			currentItemCode = dictionary.lastSearchLocation();

			if (fm.endOfFile())
			{
				break;
			}

			byteCount++;
			if (byteCount == 1024)
			{
				kByteCount++;
				byteCount = 0;
				std::cout << kByteCount << " kb read. " << fm.kbytesWritten() << " kb written.\n";
			}
		}

		fm.close();
	}
};