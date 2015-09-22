#include <stdint.h>
#include "dictionaryItem.cpp"

class LzwDictionary
{
	static const int dictionarySize = 4096;
	dictionaryItem m_Dictionary[dictionarySize];
	uint16_t codeCount = 0;
	int16_t m_lastSearchLocation = -1;
public:
	LzwDictionary()
	{
		for (int i = 0; i < 256; i++)
		{
			m_Dictionary[i] = dictionaryItem(i);
		}

		codeCount = 256;
	}

	dictionaryItem* search(dictionaryItem *root, uint8_t addition)
	{
		for (int i = 0; i < 4096; i++)
		{
			if (m_Dictionary[i].matches(root, addition))
			{
				m_lastSearchLocation = i;
				return &(m_Dictionary[i]);
			}
		}

		return nullptr;
	}

	int16_t lastSearchLocation()
	{
		return m_lastSearchLocation;
	}

	void addCode(dictionaryItem* root, uint8_t addition)
	{
		if (codeCount >= dictionarySize)
		{
			return;
		}

		m_Dictionary[codeCount] = dictionaryItem(root, addition);
		codeCount++;
	}

	dictionaryItem* getSymbol(uint16_t index)
	{
		return &(m_Dictionary[index]);
	}

};