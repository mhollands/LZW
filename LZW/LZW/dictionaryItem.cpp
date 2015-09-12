#include <vector>

class dictionaryItem
{
private:
	dictionaryItem *m_root;
	char m_addition;

public:
	dictionaryItem(char root)
	{
		m_root = nullptr;
		m_addition = root;
	}

	dictionaryItem(dictionaryItem* root, char addition)
	{
		m_root = root;
		m_addition = addition;
	}

	std::vector<char> getValue()
	{
		if (m_root == nullptr)
		{
			return std::vector<char>(m_addition);
		}

		std::vector<char> value = m_root->getValue();
		value.push_back(m_addition);

		return value;
	}
};