#pragma once
#include "ClassB.h"

class ClassC_private : private ClassB
{
public :
	void Cprivate_public() const {
		cout << endl;
		cout << "private�� ����� Ŭ���� ���ο��� ȣ��" << endl;
		
		cout << endl;
		cout << "A�� public     : ���� ���� ";     Apublic();
		cout << "A�� protected  : ���� ���� ";     Aprotected();
		cout << "A�� private    : ���� �Ұ� "    /*Aprivate(); */ << endl;
		cout << "B�� public     : ���� ���� ";     Bpublic();
		cout << "B�� protected  : ���� ���� ";     Bprotected();
		cout << "B�� private    : ���� �Ұ� "    /*Bprivate(); */ << endl;
	}
public:
	ClassC_private()
	{
		cout << "private ���" << endl;
	}


	~ClassC_private()
	{
	}

};

