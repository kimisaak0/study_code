#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::for_each;
using std::bind2nd;
using std::mem_fun_ref;
using std::mem_fun;
using std::generate_n;
using std::back_inserter;

//#define mem_fun1 mem_fun
class person
{
private:
	string name;

public:
	//...
	void print() const
	{
		cout << name << endl;
	}

	void show(int iData) const 
	{
		cout << name << "[" << iData << "]" << endl;
	}

	void printWithPrefix(string prefix) const {
		cout << prefix << name << endl;
	}
};

void foo(const vector<person>& coll)
{
	//일반 템플릿 객체의 멤버함수 호출(인자값 없는)
	for_each(coll.begin(), coll.end(), mem_fun_ref(&person::print));
	//일반 템플릿 객체의 멤버함수 호출(인자값 있는)
	for_each(coll.begin(), coll.end(), bind2nd(mem_fun_ref(&person::printWithPrefix), "person: "));
}

void prtfoo(const vector<person*>& coll) 
{
	//포인터 템플릿 객체의 멤버 함수 호출(인자값 없는)
	for_each(coll.begin(), coll.end(), mem_fun(&person::print));
	//포인터 템플릿 객체의 멤버 함수 호출(인자값 있는)
	for_each(coll.begin(), coll.end(), bind2nd(mem_fun(&person::printWithPrefix), "person: "));
}

person setData()
{
	person ret;
	return ret;
}

void g_fun(person& pData)
{
	pData.print();
}
