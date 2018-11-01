#pragma once
#include <iostream>
#include <string>
using namespace std;

//클래스 템플릿
template <class key, class value> class dictionary
{
	key* keys;
	value* values;
	int size;
	int max_size;

public:
	void add(key k, value v);
	void print();

	dictionary(int initial_size);
	
};

//클래스 템플릿 부분 특수화 
template <class value> class dictionary<int, value>
{
	int* keys;
	value* values;
	int size;
	int max_size;

public:
	void add(int key, value v);
	void print();
	void sort();

	dictionary(int initial_size);
};


//클래스 템플릿의 멤버 함수를 cpp파일에 따로 정의할 경우 
//확인할 수 없는 외부기호라는 링크 에러가 뜬다.
//이에 대한 자세한 내용은 템플릿이 클래스를 어떻게 만드는지와 
//obj파일이 어떻게 생성되는지에 대해서 확인할 것.

//클래스 템플릿 멤버 함수 정의

template<class key, class value>
dictionary<key, value>::dictionary(int initial_size) : size(0) {
	max_size = 1;
	while (initial_size >= max_size) {
		max_size *= 2;
	}
	keys = new key[max_size];
	values = new value[max_size];
}

template<class key, class value>
void dictionary<key, value>::add(key k, value v)
{
	key* tmpKey;
	value* tmpVal;

	if (size + 1 >= max_size) {
		max_size *= 2;
		tmpKey = new key[max_size];
		tmpVal = new value[max_size];

		for (int iCnt = 0; iCnt < size; iCnt++) {
			tmpKey[iCnt] = keys[iCnt];
			tmpVal[iCnt] = values[iCnt];
		}

		tmpKey[size] = k;
		tmpVal[size] = v;

		delete[] keys;
		delete[] values;

		keys = tmpKey;
		values = tmpVal;
	}

	else {
		keys[size] = k;
		values[size] = v;
	}
	size++;
}

template<class key, class value>
void dictionary<key, value>::print()
{
	for (int iCnt = 0; iCnt < size; iCnt++) {
		cout << "{" << keys[iCnt] << ", " << values[iCnt] << "}" << endl;
	}
	cout << endl;
}

//특수화 한 클래스 템플릿 멤버 함수 정의

template <class value>
dictionary<int, value>::dictionary(int initial_size)
{
	max_size = 1;
	while (initial_size >= max_size) {
		max_size *= 2;
	}
	keys = new int[max_size];
	values = new value[max_size];
}

template <class value>
void dictionary<int, value>::add(int key, value v)
{
	int* tmpKey;
	value* tmpVal;

	if (size + 1 >= max_size) {
		max_size *= 2;
		tmpKey = new int[max_size];
		tmpVal = new value[max_size];

		for (int iCnt = 0; iCnt < size; iCnt++) {
			tmpKey[iCnt] = keys[iCnt];
			tmpVal[iCnt] = values[iCnt];
		}

		tmpKey[size] = key;
		tmpVal[size] = v;

		delete[] keys;
		delete[] values;

		keys = tmpKey;
		values = tmpVal;
	}

	else {
		keys[size] = key;
		values[size] = v;
	}
	size++;

}

template <class value>
void dictionary<int, value>::print()
{
	for (int iCnt = 0; iCnt < size; iCnt++) {
		cout << "{" << keys[iCnt] << ", " << values[iCnt] << "}" << endl;
	}
	cout << endl;
}

template <class value>
void dictionary<int, value>::sort()
{
	int smallest = 0;
	for (int iCnt = 0; iCnt < size - 1; iCnt++) {
		for (int jCnt = iCnt; jCnt < size; jCnt++) {
			if (keys[jCnt] < keys[smallest]) {
				smallest = jCnt;
			}
		}
		swap(keys[iCnt], keys[smallest]);
		swap(values[iCnt], values[smallest]);
	}
}

