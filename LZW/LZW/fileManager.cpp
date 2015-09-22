#include <fstream>
#include <stdint.h>
#include <vector>

class fileManager
{
private:
	std::fstream m_inStream;
	std::fstream m_outStream;
	char writeBuffer = 0x00;
	bool writeBufferSet = false;
	char readBuffer = 0x00;
	bool readBufferSet = false;
	long m_bytesWritten = 0;
	long m_bytesRead = 0;

	void flushBuffer()
	{
		if (writeBufferSet == false)
		{
			return;
		}

		writeByte(writeBuffer);
		writeBuffer = 0;
		writeBufferSet = false;
	}

public:
	fileManager(char* fileName, char* output)
	{
		m_inStream.open(fileName, std::ios::in | std::ofstream::binary);
		m_outStream.open(output, std::ios::out | std::ofstream::binary);
	}

	long bytesWritten()
	{
		return m_bytesWritten;
	}

	long kbytesWritten()
	{
		return m_bytesWritten/1024;
	}

	long bytesRead()
	{
		return m_bytesRead;
	}

	long kbytesRead()
	{
		return m_bytesRead / 1024;
	}

	void writeByte(char byte)
	{
		m_outStream.write(&byte, 1);
		m_bytesWritten++;
	}

	char readByte()
	{
		char data[1];
		m_inStream.read(data, 1);
		m_bytesRead++;

		return data[0];
	}

	void writeCode(uint16_t data)
	{
		if (!writeBufferSet)
		{
			char low = (data & 0x0f);
			char high = ((data >> 4) & 0xff);

			writeByte(high);

			writeBuffer = (low << 4);
			writeBufferSet = true;
			return;
		}

		char high = ((data >> 8) & 0x0f) | writeBuffer;
		char low = data & 0xff;
				
		writeByte(high);
		writeByte(low);

		writeBuffer = 0;
		writeBufferSet = false;
	}

	void writeSymbol(std::vector<uint8_t> data)
	{
		for (unsigned int i = 0; i < data.size(); i++)
		{
			writeByte(data[i]);
		}
	}

	uint16_t readCode()
	{
		if (!readBufferSet)
		{
			char data[2];
			m_inStream.read(data, 2);
			m_bytesRead += 2;
			readBuffer = (data[1] & 0x0f);
			readBufferSet = true;
			return ((data[0] << 4) & 0xff0) | ((data[1] >> 4) & 0x0f);
		}
		
		char data[1];
		m_inStream.read(data, 1);
		m_bytesRead++;
		uint16_t code = ((readBuffer << 8) &0x0ff0) | (data[0] & 0xff);

		readBuffer = 0;
		readBufferSet = false;

		return code;
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