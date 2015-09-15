#include "LZW Manager.cpp"

int main()
{
	LzwManager manager;
	manager.compress("shakespeare.txt");

	return 0;
}