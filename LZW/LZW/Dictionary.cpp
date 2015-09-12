#include <stdint.h>
#include "dictionaryItem.cpp"

class LzwDictionary
{
	dictionaryItem m_Dictionary[4096];
	uint16_t codeCount = 0;
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
				return &(m_Dictionary[i]);
			}
		}

		return nullptr;
	}

	void addCode(dictionaryItem root, uint8_t addition)
	{
		m_Dictionary[codeCount] = dictionaryItem(&root, addition);
	}
};