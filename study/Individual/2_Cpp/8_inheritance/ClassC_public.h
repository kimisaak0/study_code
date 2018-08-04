#pragma once
#include "ClassB.h"

class ClassC_public : public ClassB
{
public:
	void Cpublic_public() const {
		cout << endl;
		cout << "public으로 상속한 클래스 내부에서 호출" << endl;

		cout << endl;
		cout << "A의 public     : 접근 가능 ";     Apublic();
		cout << "A의 protected  : 접근 가능 ";     Aprotected();
		cout << "A의 private    : 접근 불가 "    /*Aprivate(); */ << endl;
		cout << "B의 public     : 접근 가능 ";     Bpublic();
		cout << "B의 protected  : 접근 가능 ";     Bprotected();
		cout << "B의 private    : 접근 불가 "    /*Bprivate(); */ << endl;
	}
public:
	ClassC_public()
	{
		cout << "public 상속" << endl;
	}


	~ClassC_public()
	{
	}
};

