#include <fstream>
#include <stdint.h>

class fileManager
{
private:
	std::fstream m_inStream;
	std::fstream m_outStream;
	char buffer = 0x00;
	long m_bytesWritten = 0;

	void writeByte(char byte)
	{
		m_outStream.write(&byte, 1);
		m_bytesWritten++;
	}

	void flushBuffer()
	{
		if (buffer == 0)
		{
			return;
		}

		writeByte(buffer);
		buffer = 0;
	}

public:
	fileManager(char* fileName)
	{
		m_inStream.open(fileName, std::ios::in | std::ios_base::binary);
		m_outStream.open("output.txt", std::ios::out);
	}

	long bytesWritten()
	{
		return m_bytesWritten;
	}

	long kbytesWritten()
	{
		return m_bytesWritten/1024;
	}

	char readByte()
	{
		char data[1];
		m_inStream.read(data, 1);

		return data[0];
	}

	void writeCode(int16_t data)
	{
		char low = (data & 0x0f);
		char high = ((data >> 4) & 0xff);

		writeByte(high);

		if (buffer == 0)
		{
			buffer = (low << 4);
			return;
		}

		buffer |= low;
		
		writeByte(buffer);

		buffer = 0;
	}

	bool endOfFile()
	{
		return m_inStream.eof();
	}

	void close()
	{
		flushBuffer();
		m_inStream.close();
		m_outStream.close();
	}
};