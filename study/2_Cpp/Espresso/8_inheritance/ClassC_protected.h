#pragma once
#include "ClassB.h"

class ClassC_protected : protected ClassB
{
public:
	void Cprotected_public() const {
		cout << endl;
		cout << "protected�� ����� Ŭ���� ���ο��� ȣ��" << endl;

		cout << endl;
		cout << "A�� public     : ���� ���� ";     Apublic();
		cout << "A�� protected  : ���� ���� ";     Aprotected();
		cout << "A�� private    : ���� �Ұ� "    /*Aprivate(); */ << endl;
		cout << "B�� public     : ���� ���� ";     Bpublic();
		cout << "B�� protected  : ���� ���� ";     Bprotected();
		cout << "B�� private    : ���� �Ұ� "    /*Bprivate(); */ << endl;
	}
public:
	ClassC_protected()
	{
		cout << "protected ���" << endl;
	}


	~ClassC_protected()
	{
	}

};

