#pragma once

// 어차피 멤버 함수를 클래스 템플릿 외부에 정의해서 다른 파일로 분리할 수 없으니
// 클래스 템플릿 안에다가 인라인으로 넣어버림.


// 기본 타입 클래스 템플릿
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

// 포인터 타입 클래스 템플릿에 대한 부분 특수화
// NULL을 검사하도록 (컬렉션이 수정 및 저장소 유형
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