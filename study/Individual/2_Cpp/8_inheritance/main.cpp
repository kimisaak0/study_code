#include "ClassB.h"
#include "ClassC_private.h"
#include "ClassC_protected.h"
#include "ClassC_public.h"

int main()
{
	{
		ClassA superClass;

		cout << endl;
		cout << "ClassA : superClass" << endl;

		cout << endl;
		//superClass.Aprivate();	//객체에서 private 멤버 함수 접근 불가
		//superClass.Aprotected();	//객체에서 protected 멤버 함수 접근 불가
		superClass.Apublic();		//객체에서 public 멤버 함수 접근 가능

		cout << endl;
		cout << "main()에서 ClassA의 객체로 호출" << endl;

		cout << endl;
		cout << "A의 public 변수    : 접근 가능 "; cout		<< superClass.m_iPublicA      << endl;
		cout << "A의 protected 변수 : 접근 불가 "; cout /*	<< superClass.m_iProtectedA*/ << endl;
		cout << "A의 private 변수   : 접근 불가 "; cout /*	<< superClass.m_iPrivateA */  << endl;
		cout << "A의 public 함수    : 접근 가능 ";				  superClass.Apublic();
		cout << "A의 protected 함수 : 접근 불가 " << endl;		//superClass.Aprotected();
		cout << "A의 private 함수   : 접근 불가 " << endl;		//superClass.Aprivate();

		cout << endl;
		cout << "재정의 함수 호출" << endl;

		cout << endl;
		cout << "재정의 전 멤버 변수            : "  <<			superClass.m_iID << endl;
		cout << "재정의 전 멤버 함수 showID     : ";	        superClass.showID();
		cout << "재정의 전 멤버 함수 overriding : ";			superClass.overriding();

		cout << endl;
	}

	{
		ClassB subClass;

		cout << endl;
		cout << "ClassB : subClass" << endl;

		cout << endl;
		//subClass.Aprivate();		//객체에서 부모의 private 멤버 접근 불가
		//subClass.Aprotected();	//객체에서 부모의 protected 멤버 접근 불가
		subClass.Apublic();			//객체에서 부모의 public 멤버 접근 가능

		//subClass.Bprivate();		//객체에서 private 멤버 접근 불가
		//subClass.Bprotected();	//객체에서 protected 멤버 접근 불가
		subClass.Bpublic();			//객체에서 public 멤버 접근 가능
		
		cout << endl;
		subClass.AinB();

		cout << endl;
		cout << "main()에서 ClassB의 객체로 호출" << endl;

		cout << endl;
		cout << "A의 public 변수    : 접근 가능 "; cout		<< subClass.m_iPublicA      << endl;
		cout << "A의 protected 변수 : 접근 불가 "; cout /*	<< subClass.m_iProtectedA*/ << endl;
		cout << "A의 private 변수   : 접근 불가 "; cout /*	<< subClass.m_iPrivateA */  << endl;
		cout << "A의 public 함수    : 접근 가능 ";             subClass.Apublic();
		cout << "A의 protected 함수 : 접근 불가 " << endl;   //subClass.Aprotected();
		cout << "A의 private 함수   : 접근 불가 " << endl;   //subClass.Aprivate();

		cout << endl;
		cout << "재정의 함수 호출" << endl;

		cout << endl;
		cout << "재정의 후 멤버 변수            : " <<   subClass.m_iID << endl;	// 재정의된 멤버 변수
		cout << "재정의 후 멤버 함수 showID     : ";     subClass.showID();         // 재정의된 멤버 변수가 포함되어 있지만 A의 함수가 호출된다.
		cout << "재정의 후 멤버 함수 overriding : ";     subClass.overriding();     // 재정의된 멤버 함수

		cout << endl;
	}

	{
		const ClassC_private privateClass;

		cout << endl;
		cout << "ClassC : subsubClass" << endl;

		cout << endl;
		cout << "private 상속" << endl;

		cout << endl;
		privateClass.Cprivate_public();

		cout << endl;
		cout << "private로 상속한 클래스 외부 객체에서 호출" << endl;

		cout << endl;
		cout << "A의 public    : 접근 불가 " << endl;		//privateClass.Apublic();
		cout << "A의 protected : 접근 불가 " << endl;		//privateClass.Aprotected();
		cout << "A의 private   : 접근 불가 " << endl;		//privateClass.Aprivate();
		cout << "B의 public    : 접근 불가 " << endl;		//privateClass.Bpublic();
		cout << "B의 protected : 접근 불가 " << endl;		//privateClass.Bprotected();
		cout << "B의 private   : 접근 불가 " << endl;		//privateClass.Bprivate();
		
		cout << endl;

	}

	{
		const ClassC_protected protectedClass;

		cout << endl;
		cout << "ClassC : subsubClass" << endl;

		cout << endl;
		cout << "protected 상속" << endl;

		cout << endl;
		protectedClass.Cprotected_public();

		cout << endl;
		cout << "protected로 상속한 클래스 외부 객체에서 호출" << endl;

		cout << endl;
		cout << "A의 public    : 접근 불가 " << endl;		//protectedClass.Apublic();
		cout << "A의 protected : 접근 불가 " << endl;		//protectedClass.Aprotected();
		cout << "A의 private   : 접근 불가 " << endl;		//protectedClass.Aprivate();
		cout << "B의 public    : 접근 불가 " << endl;		//protectedClass.Bpublic();
		cout << "B의 protected : 접근 불가 " << endl;		//protectedClass.Bprotected();
		cout << "B의 private   : 접근 불가 " << endl;		//protectedClass.Bprivate();

		cout << endl;

	}

	{
		const ClassC_public publicClass;
	
		cout << endl;
		cout << "ClassC : subsubClass" << endl;
		
		cout << endl;
		cout << "public 상속" << endl;

		cout << endl;
		publicClass.Cpublic_public();

		cout << endl;
		cout << "public으로 상속한 클래스 외부 객체에서 호출" << endl;

		cout << endl;
		cout << "A의 public     : 접근 가능 ";    publicClass.Apublic();
		cout << "A의 protected  : 접근 불가 "  /* publicClass.Aprotected(); */ <<endl;
		cout << "A의 private    : 접근 불가 "  /* publicClass.Aprivate();   */ <<endl;		
		cout << "B의 public     : 접근 가능 ";    publicClass.Bpublic();
		cout << "B의 protected  : 접근 불가 "  /* publicClass.Bprotected(); */ <<endl;
		cout << "B의 private    : 접근 불가 "  /* publicClass.Bprivate();   */ <<endl;

		cout << endl; 

	}
}