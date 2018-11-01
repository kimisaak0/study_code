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
	//�Ϲ� ���ø� ��ü�� ����Լ� ȣ��(���ڰ� ����)
	for_each(coll.begin(), coll.end(), mem_fun_ref(&person::print));
	//�Ϲ� ���ø� ��ü�� ����Լ� ȣ��(���ڰ� �ִ�)
	for_each(coll.begin(), coll.end(), bind2nd(mem_fun_ref(&person::printWithPrefix), "person: "));
}

void prtfoo(const vector<person*>& coll) 
{
	//������ ���ø� ��ü�� ��� �Լ� ȣ��(���ڰ� ����)
	for_each(coll.begin(), coll.end(), mem_fun(&person::print));
	//������ ���ø� ��ü�� ��� �Լ� ȣ��(���ڰ� �ִ�)
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
