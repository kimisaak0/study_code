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
		//superClass.Aprivate();	//��ü���� private ��� �Լ� ���� �Ұ�
		//superClass.Aprotected();	//��ü���� protected ��� �Լ� ���� �Ұ�
		superClass.Apublic();		//��ü���� public ��� �Լ� ���� ����

		cout << endl;
		cout << "main()���� ClassA�� ��ü�� ȣ��" << endl;

		cout << endl;
		cout << "A�� public ����    : ���� ���� "; cout		<< superClass.m_iPublicA      << endl;
		cout << "A�� protected ���� : ���� �Ұ� "; cout /*	<< superClass.m_iProtectedA*/ << endl;
		cout << "A�� private ����   : ���� �Ұ� "; cout /*	<< superClass.m_iPrivateA */  << endl;
		cout << "A�� public �Լ�    : ���� ���� ";				  superClass.Apublic();
		cout << "A�� protected �Լ� : ���� �Ұ� " << endl;		//superClass.Aprotected();
		cout << "A�� private �Լ�   : ���� �Ұ� " << endl;		//superClass.Aprivate();

		cout << endl;
		cout << "������ �Լ� ȣ��" << endl;

		cout << endl;
		cout << "������ �� ��� ����            : "  <<			superClass.m_iID << endl;
		cout << "������ �� ��� �Լ� showID     : ";	        superClass.showID();
		cout << "������ �� ��� �Լ� overriding : ";			superClass.overriding();

		cout << endl;
	}

	{
		ClassB subClass;

		cout << endl;
		cout << "ClassB : subClass" << endl;

		cout << endl;
		//subClass.Aprivate();		//��ü���� �θ��� private ��� ���� �Ұ�
		//subClass.Aprotected();	//��ü���� �θ��� protected ��� ���� �Ұ�
		subClass.Apublic();			//��ü���� �θ��� public ��� ���� ����

		//subClass.Bprivate();		//��ü���� private ��� ���� �Ұ�
		//subClass.Bprotected();	//��ü���� protected ��� ���� �Ұ�
		subClass.Bpublic();			//��ü���� public ��� ���� ����
		
		cout << endl;
		subClass.AinB();

		cout << endl;
		cout << "main()���� ClassB�� ��ü�� ȣ��" << endl;

		cout << endl;
		cout << "A�� public ����    : ���� ���� "; cout		<< subClass.m_iPublicA      << endl;
		cout << "A�� protected ���� : ���� �Ұ� "; cout /*	<< subClass.m_iProtectedA*/ << endl;
		cout << "A�� private ����   : ���� �Ұ� "; cout /*	<< subClass.m_iPrivateA */  << endl;
		cout << "A�� public �Լ�    : ���� ���� ";             subClass.Apublic();
		cout << "A�� protected �Լ� : ���� �Ұ� " << endl;   //subClass.Aprotected();
		cout << "A�� private �Լ�   : ���� �Ұ� " << endl;   //subClass.Aprivate();

		cout << endl;
		cout << "������ �Լ� ȣ��" << endl;

		cout << endl;
		cout << "������ �� ��� ����            : " <<   subClass.m_iID << endl;	// �����ǵ� ��� ����
		cout << "������ �� ��� �Լ� showID     : ";     subClass.showID();         // �����ǵ� ��� ������ ���ԵǾ� ������ A�� �Լ��� ȣ��ȴ�.
		cout << "������ �� ��� �Լ� overriding : ";     subClass.overriding();     // �����ǵ� ��� �Լ�

		cout << endl;
	}

	{
		const ClassC_private privateClass;

		cout << endl;
		cout << "ClassC : subsubClass" << endl;

		cout << endl;
		cout << "private ���" << endl;

		cout << endl;
		privateClass.Cprivate_public();

		cout << endl;
		cout << "private�� ����� Ŭ���� �ܺ� ��ü���� ȣ��" << endl;

		cout << endl;
		cout << "A�� public    : ���� �Ұ� " << endl;		//privateClass.Apublic();
		cout << "A�� protected : ���� �Ұ� " << endl;		//privateClass.Aprotected();
		cout << "A�� private   : ���� �Ұ� " << endl;		//privateClass.Aprivate();
		cout << "B�� public    : ���� �Ұ� " << endl;		//privateClass.Bpublic();
		cout << "B�� protected : ���� �Ұ� " << endl;		//privateClass.Bprotected();
		cout << "B�� private   : ���� �Ұ� " << endl;		//privateClass.Bprivate();
		
		cout << endl;

	}

	{
		const ClassC_protected protectedClass;

		cout << endl;
		cout << "ClassC : subsubClass" << endl;

		cout << endl;
		cout << "protected ���" << endl;

		cout << endl;
		protectedClass.Cprotected_public();

		cout << endl;
		cout << "protected�� ����� Ŭ���� �ܺ� ��ü���� ȣ��" << endl;

		cout << endl;
		cout << "A�� public    : ���� �Ұ� " << endl;		//protectedClass.Apublic();
		cout << "A�� protected : ���� �Ұ� " << endl;		//protectedClass.Aprotected();
		cout << "A�� private   : ���� �Ұ� " << endl;		//protectedClass.Aprivate();
		cout << "B�� public    : ���� �Ұ� " << endl;		//protectedClass.Bpublic();
		cout << "B�� protected : ���� �Ұ� " << endl;		//protectedClass.Bprotected();
		cout << "B�� private   : ���� �Ұ� " << endl;		//protectedClass.Bprivate();

		cout << endl;

	}

	{
		const ClassC_public publicClass;
	
		cout << endl;
		cout << "ClassC : subsubClass" << endl;
		
		cout << endl;
		cout << "public ���" << endl;

		cout << endl;
		publicClass.Cpublic_public();

		cout << endl;
		cout << "public���� ����� Ŭ���� �ܺ� ��ü���� ȣ��" << endl;

		cout << endl;
		cout << "A�� public     : ���� ���� ";    publicClass.Apublic();
		cout << "A�� protected  : ���� �Ұ� "  /* publicClass.Aprotected(); */ <<endl;
		cout << "A�� private    : ���� �Ұ� "  /* publicClass.Aprivate();   */ <<endl;		
		cout << "B�� public     : ���� ���� ";    publicClass.Bpublic();
		cout << "B�� protected  : ���� �Ұ� "  /* publicClass.Bprotected(); */ <<endl;
		cout << "B�� private    : ���� �Ұ� "  /* publicClass.Bprivate();   */ <<endl;

		cout << endl; 

	}
}