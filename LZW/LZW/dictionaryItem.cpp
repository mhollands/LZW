#include <vector>

#include <stdint.h>

class dictionaryItem
{
private:
	dictionaryItem *m_root;
	uint8_t m_addition;

public:
	dictionaryItem()
	{

	}

	dictionaryItem(uint8_t root)
	{
		m_root = nullptr;
		m_addition = root;
	}

	dictionaryItem(dictionaryItem* root, uint8_t addition)
	{
		m_root = root;
		m_addition = addition;
	}

	bool matches(dictionaryItem* root, uint8_t addition)
	{
		if (m_root == root && m_addition == addition)
		{
			return true;
		}

		return false;
	}

	std::vector<uint8_t> getValue()
	{
		if (m_root == nullptr)
		{
			return std::vector<uint8_t>(m_addition);
		}

		std::vector<uint8_t> value = m_root->getValue();
		value.push_back(m_addition);

		return value;
	}
};