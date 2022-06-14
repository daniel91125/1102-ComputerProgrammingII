#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "deque - Student ID - hw8.h"

void testCopyConstructor();
void testCopyConstructor1();
void testCopyConstructor2();
void testDeque1(size_t size);
void testDeque2(size_t size);
void testDeque3(size_t size);
void testDeque4(size_t size);
void testDeque5();

bool equal(std::deque< int >& deque1, deque< int >& deque2);

const unsigned int number = 200;

int main()
{
	for (unsigned int seed = 1; seed <= 10; seed++)
	{
		srand(seed);
		testCopyConstructor();
	}

	cout << endl;

	testCopyConstructor1();
	testCopyConstructor2();


	for (size_t i = 1; i <= 10; i++)
	{
		testDeque1(8 * i);
		testDeque2(8 * i);
		testDeque3(8 * i);
		testDeque4(8 * i);
	}

	cout << endl;

	for (unsigned int seed = 1; seed <= 50; seed++)
	{
		srand(seed);
		testDeque5();
	}

	cout << endl;

	system("pause");
}

void testCopyConstructor()
{
	unsigned int numErrors = number;
	unsigned int length;
	int value;
	for (unsigned int i = 0; i < number; i++)
	{
		std::deque< int > deque1;
		deque< int > deque2;
		length = rand() % 200;

		for (unsigned int j = 0; j < length; j++)
		{
			value = 1 + rand() % 99;
			deque1.push_front(value);
			deque2.push_front(value);
		}

		std::deque< int > deque3(deque1);
		deque< int > deque4(deque2);

		if (equal(deque3, deque4))
			numErrors--;
	}

	cout << "There are " << numErrors << " errors\n";
}

void testCopyConstructor1()
{
	std::deque< int > deque1;
	deque< int > deque2;

	deque1.push_front(1);
	deque2.push_front(1);

	for (int i = 2; i <= 60; i++)
	{
		deque1.push_back(i);
		deque2.push_back(i);
	}

	for (int i = 1; i <= 32; i++)
	{
		deque1.pop_front();
		deque2.pop_front();
	}

	if (equal(deque1, deque2))
		cout << "Correct!\n\n";
	else
		cout << "Incorrect!\n\n";

	for (int i = 61; i <= 92; i++)
	{
		deque1.push_back(i);
		deque2.push_back(i);
	}

	if (equal(deque1, deque2))
		cout << "Correct!\n\n";
	else
		cout << "Incorrect!\n\n";

	for (int i = 1; i <= 59; i++)
	{
		deque1.pop_front();
		deque2.pop_front();
	}

	if (equal(deque1, deque2))
		cout << "Correct!\n\n";
	else
		cout << "Incorrect!\n\n";


	std::deque< int > deque3(deque1);
	deque< int > deque4(deque2);

	if (equal(deque3, deque4))
		cout << "Correct!\n\n";
	else
		cout << "Incorrect!\n\n";
}

void testCopyConstructor2()
{
	std::deque< int> deque1;
	deque< int > deque2;

	deque1.push_front(1);
	deque2.push_front(1);

	for (int i = 2; i <= 125; i++)
	{
		deque1.push_back(i);
		deque2.push_back(i);
	}

	for (int i = 1; i <= 96; i++)
	{
		deque1.pop_front();
		deque2.pop_front();
	}

	if (equal(deque1, deque2))
		cout << "Correct!\n\n";
	else
		cout << "Incorrect!\n\n";

	for (int i = 126; i <= 221; i++)
	{
		deque1.push_back(i);
		deque2.push_back(i);
	}

	if (equal(deque1, deque2))
		cout << "Correct!\n\n";
	else
		cout << "Incorrect!\n\n";

	for (int i = 1; i <= 124; i++)
	{
		deque1.pop_front();
		deque2.pop_front();
	}

	if (equal(deque1, deque2))
		cout << "Correct!\n\n";
	else
		cout << "Incorrect!\n\n";


	std::deque< int > deque3(deque1);
	deque< int > deque4(deque2);

	if (equal(deque3, deque4))
		cout << "Correct!\n\n";
	else
		cout << "Incorrect!\n\n";

}


void testDeque1(size_t size)
{
	unsigned int numErrors = 8;
	for (unsigned int k = 0; k < 4; k++)
	{
		std::deque< int > deque1;
		unsigned int i;
		for (i = 1; i <= 4 * (size / 2 - 1) + k; i++)
			deque1.push_back(i);
		for (; i <= 4 * (size - 1) + k; i++)
			deque1.push_front(i);

		deque< int > deque2;
		unsigned int j;
		for (j = 1; j <= 4 * (size / 2 - 1) + k; j++)
			deque2.push_back(j);
		for (; j <= 4 * (size - 1) + k; j++)
			deque2.push_front(j);

		if (equal(deque1, deque2))
			numErrors--;

		deque1.push_front(i);
		deque2.push_front(j);

		if (equal(deque1, deque2))
			numErrors--;
	}
	cout << "There are " << numErrors << " errors.\n";
}

void testDeque2(size_t size)
{
	unsigned int numErrors = 8;
	for (unsigned int k = 0; k < 4; k++)
	{
		std::deque< int > deque1;
		unsigned int i;
		for (i = 1; i <= 4 * (size / 2 - 1) + k; i++)
			deque1.push_back(i);
		for (; i <= 4 * (size - 1) + k; i++)
			deque1.push_front(i);

		deque< int > deque2;
		unsigned int j;
		for (j = 1; j <= 4 * (size / 2 - 1) + k; j++)
			deque2.push_back(j);
		for (; j <= 4 * (size - 1) + k; j++)
			deque2.push_front(j);

		if (equal(deque1, deque2))
			numErrors--;

		deque1.push_back(i);
		deque2.push_back(j);

		if (equal(deque1, deque2))
			numErrors--;
	}
	cout << "There are " << numErrors << " errors.\n";
}

void testDeque3(size_t size)
{
	unsigned int numErrors = 8;
	for (unsigned int k = 0; k < 4; k++)
	{
		std::deque< int > deque1;
		unsigned int i;
		for (i = 1; i <= 4 * (size / 2 - 1) + k; i++)
			deque1.push_front(i);
		for (; i <= 4 * (size - 1) + k; i++)
			deque1.push_back(i);

		deque< int > deque2;
		unsigned int j;
		for (j = 1; j <= 4 * (size / 2 - 1) + k; j++)
			deque2.push_front(j);
		for (; j <= 4 * (size - 1) + k; j++)
			deque2.push_back(j);

		if (equal(deque1, deque2))
			numErrors--;

		deque1.push_back(i);
		deque2.push_back(j);

		if (equal(deque1, deque2))
			numErrors--;
	}
	cout << "There are " << numErrors << " errors.\n";
}

void testDeque4(size_t size)
{
	unsigned int numErrors = 8;
	for (unsigned int k = 0; k < 4; k++)
	{
		std::deque< int > deque1;
		unsigned int i;
		for (i = 1; i <= 4 * (size / 2 - 1) + k; i++)
			deque1.push_front(i);
		for (; i <= 4 * (size - 1) + k; i++)
			deque1.push_back(i);

		deque< int > deque2;
		unsigned int j;
		for (j = 1; j <= 4 * (size / 2 - 1) + k; j++)
			deque2.push_front(j);
		for (; j <= 4 * (size - 1) + k; j++)
			deque2.push_back(j);

		if (equal(deque1, deque2))
			numErrors--;

		deque1.push_front(i);
		deque2.push_front(j);

		if (equal(deque1, deque2))
			numErrors--;
	}
	cout << "There are " << numErrors << " errors.\n";
}

void testDeque5()
{
	std::deque< int > deque1;
	deque< int > deque2;

	unsigned int numErrors = 1001;
	if (equal(deque1, deque2))
		numErrors--;

	int value;
	for (unsigned int i = 0; i < 1000; i++)
	{
		switch (rand() % 4)
		{
		case 0:
			value = 1 + rand() % 99;
			deque1.push_front(value);
			deque2.push_front(value);
			break;
		case 1:
			if (deque1.size() > 0)
			{
				deque1.pop_front();
				deque2.pop_front();
			}
			break;
		case 2:
			value = 1 + rand() % 99;
			deque1.push_back(value);
			deque2.push_back(value);
			break;
		case 3:
			if (deque1.size() > 0)
			{
				deque1.pop_back();
				deque2.pop_back();
			}
			break;
		}

		if (equal(deque1, deque2))
			numErrors--;
	}

	cout << "There are " << numErrors << " errors.\n";
}

bool equal(std::deque< int >& deque1, deque< int >& deque2)
{
	int** map1 = *(reinterpret_cast<int***> (&deque1) + 1);
	size_t mapSize1 = *(reinterpret_cast<size_t*>(&deque1) + 2);
	size_t myOff1 = *(reinterpret_cast<size_t*>(&deque1) + 3);
	size_t mySize1 = *(reinterpret_cast<size_t*>(&deque1) + 4);

	int** map2 = *(reinterpret_cast<int***> (&deque2));
	size_t mapSize2 = *(reinterpret_cast<size_t*>(&deque2) + 1);
	size_t myOff2 = *(reinterpret_cast<size_t*>(&deque2) + 2);
	size_t mySize2 = *(reinterpret_cast<size_t*>(&deque2) + 3);

	if (mapSize1 != mapSize2)
		return false;

	if (mapSize2 == 0)
		if (mySize2 == 0 && myOff2 == 0 && map2 == nullptr)
			return true;
		else
			return false;

	if (myOff1 != myOff2)
		return false;

	if (mySize1 != mySize2)
		return false;

	size_t row, col;
	//map1為std map2自己的
	for (size_t i = myOff1; i < myOff1 + mySize1; ++i/*, ++it2*/)
	{
		row = (i / 4) % mapSize1;
		if (map1[row] != nullptr && map2[row] == nullptr)
			return false;

		if (map1[row] == nullptr && map2[row] != nullptr)
			return false;

		if (map1[row] != nullptr && map2[row] != nullptr)
		{
			col = i % 4;
			if (map1[row][col] != map2[row][col])
				return false;
		}
	}

	return true;
}