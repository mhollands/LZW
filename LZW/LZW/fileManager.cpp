#include <fstream>

class fileManager
{
public:
	std::fstream m_inStream;
	std::fstream m_outStream;
	fileManager(char* fileName)
	{
		m_inStream.open(fileName, std::ios::in);
		m_outStream.open("output.txt", std::ios::out);
		char a[3] = { 'a', 'b', 'c' };
		m_outStream.write(a, 3);
		m_outStream.close();
	}

	char getByte()
	{
		char data[1];
		m_inStream.read(data, 1);

		return data[0];
	}

	bool endOfFile()
	{
		return m_inStream.eof();
	}

	void close()
	{
		m_inStream.close();
		m_outStream.close();
	}
};