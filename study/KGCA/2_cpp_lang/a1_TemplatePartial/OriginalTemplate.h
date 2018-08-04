#pragma once

// ������ ��� �Լ��� Ŭ���� ���ø� �ܺο� �����ؼ� �ٸ� ���Ϸ� �и��� �� ������
// Ŭ���� ���ø� �ȿ��ٰ� �ζ������� �־����.


// �⺻ Ÿ�� Ŭ���� ���ø�
template <class T>
class Bag
{
	T* elem;
	int size;
	int max_size;

public:
	
	void add(T t)
	{
		T* tmp;
		if (size + 1 >= max_size)	{
			max_size *= 2;
			tmp = new T[max_size];
			for (int iCnt = 0; iCnt < size; iCnt++) {
				tmp[iCnt] = elem[iCnt];
			}
			tmp[size++] = t;
			delete[] elem;
			elem = tmp;
		}
		else {
			elem[size++] = t;
		}
	}

	void print()
	{
		for (int iCnt = 0; iCnt < size; iCnt++) {
			cout << elem[iCnt] << " ";
		}
		cout << endl << endl;
	}

	void sort()
	{
		for (int a = 1; a<size; a += 1)
		{
			int temp = elem[a];
			int b = a - 1;
			while (b >= 0 && elem[b] > temp)
			{
				elem[b + 1] = elem[b];
				b -= 1;
			}
			elem[b + 1] = temp;
		}
	}

	Bag() : elem(0), size(0), max_size(1) {}

};

// ������ Ÿ�� Ŭ���� ���ø��� ���� �κ� Ư��ȭ
// NULL�� �˻��ϵ��� (�÷����� ���� �� ����� ����
template <class T>
class Bag<T*>
{
	T* elem;
	int size;
	int max_size;

public:

	void add(T* t)
	{
		T* tmp;

		if (t == nullptr)
		{
			//check for nullptr
			cout << "Null pointer!" << endl;
			return;
		}

		if (size + 1 >= max_size) {
			max_size *= 2;
			tmp = new T[max_size];
			for (int iCnt = 0; iCnt < size; iCnt++) {
				tmp[iCnt] = elem[iCnt];
			}
			tmp[size++] = *t; //Dereference
			delete[] elem;
			elem = tmp;
		}
		else {
			elem[size++] = *t; //Dereference
		}
	}

	void print()
	{
		for (int iCnt = 0; iCnt < size; iCnt++) {
			cout << elem[iCnt] << " ";
		}
		cout << endl << endl;
	}

	void sort()
	{
		for (int a = 1; a<size; a += 1)
		{
			int temp = elem[a];
			int b = a - 1;
			while (b >= 0 && elem[b] > temp)
			{
				elem[b + 1] = elem[b];
				b -= 1;
			}
			elem[b + 1] = temp;
		}
	}

	Bag() : elem(0), size(0), max_size(1) {}

};