#include "Utils.h"

int readNumber(int min, int max)
{
	int number;
	cin >> number;
	while (number < min || number > max || cin.fail())
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		cout << "Error! Insert number again: ";
		cin >> number;
	}
        cin.ignore(1000, '\n');
	return number;
}

int magnitudeOrder(int num)
{
	int ret = 0;
	int copy = num;
	while(copy>=10)
	{
		copy /= 10;
		ret++;
	}
	return ret;
}

