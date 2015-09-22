#include "LZW Manager.cpp"

int main()
{
	LzwManager manager;
	manager.compress("rnj.txt");

	manager.decompress("compressed.txt");

	return 0;
}