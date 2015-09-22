#include <stdio.h>
#include <iostream>
#include "Dictionary.cpp"
#include <fstream>
#include "fileManager.cpp"
#include <string>
class LzwManager
{
public:
	void compress(char* file)
	{
		long byteCount = 0;
		long kByteCount = 0;
		LzwDictionary dictionary;

		fileManager fm = fileManager(file, "compressed.txt");

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

	void decompress(char* file)
	{
		float byteCount = 0;
		long kByteCount = 0;
		LzwDictionary dictionary;
		fileManager fm = fileManager(file, "decompressed.txt");

		dictionaryItem* oldSymbol = nullptr;
		
		while (true)
		{
			uint16_t code = fm.readCode();

			if (fm.endOfFile())
			{
				break;
			}

			dictionaryItem* symbol = dictionary.getSymbol(code);
			std::vector<uint8_t> symbolText = symbol->getValue();
			
			fm.writeSymbol(symbolText);
			byteCount += symbolText.size();

			if (oldSymbol != nullptr)
			{
				dictionary.addCode(oldSymbol, symbolText[0]);
			}

			oldSymbol = symbol;

			if (byteCount >= 1024)
			{
				kByteCount++;
				byteCount -= 1024;
				std::cout << kByteCount << " kb written. " << fm.kbytesRead() << " kb read.\n";
			}
		}

		fm.close();
	}
};