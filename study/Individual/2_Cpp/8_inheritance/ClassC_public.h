#pragma once
#include "ClassB.h"

class ClassC_public : public ClassB
{
public:
	void Cpublic_public() const {
		cout << endl;
		cout << "public���� ����� Ŭ���� ���ο��� ȣ��" << endl;

		cout << endl;
		cout << "A�� public     : ���� ���� ";     Apublic();
		cout << "A�� protected  : ���� ���� ";     Aprotected();
		cout << "A�� private    : ���� �Ұ� "    /*Aprivate(); */ << endl;
		cout << "B�� public     : ���� ���� ";     Bpublic();
		cout << "B�� protected  : ���� ���� ";     Bprotected();
		cout << "B�� private    : ���� �Ұ� "    /*Bprivate(); */ << endl;
	}
public:
	ClassC_public()
	{
		cout << "public ���" << endl;
	}


	~ClassC_public()
	{
	}
};

