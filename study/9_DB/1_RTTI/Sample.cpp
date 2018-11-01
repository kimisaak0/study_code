#include <iostream>
#include <typeinfo.h>
//#include <list>
#include <queue>

#define DECLARE_CLASSNAME static char lpszClassName[]
#define IMPLEMENT_CLASSNAME(s) char s##::lpszClassName[] = (#s);

#define DECLARE_DYNCREATE static CObject* CreateObject();
#define IMPLEMENT_DYNCREATE(s) CObject* s::CreateObject()	{return new s;}

#define DECLARE_DYNAMIC(s) static CRuntimeClass class##s;
#define IMPLEMENT_DYNAMIC(s) CRuntimeClass s::class##s={ #s, sizeof(s), s::CreateObject }

#define DECLARE_DYNCLASS_CREATE CRuntimeClass* GetRuntimeClass() const;
#define IMPLEMENT_DYNCLASS_CREATE(s) CRuntimeClass* s::GetRuntimeClass() const{return &class##s;}

#define RUNTIME_CLASS(s) &s::class##s;


class CObject;
//핵심!!!
class CRuntimeClass 
{
public:
	char m_lpszClassName[21];
	int  m_iObjectSize;
	CObject* (*pfnCreateObject)();
	CObject* CreateObject()
	{
		return (*pfnCreateObject)();
	}
};

class CObject
{
public:
	static CRuntimeClass classCObject; //DECLARE_DYNAMIC(CObject);
	static char lpszClassName[];       //DECLARE_CLASSNAME;
	virtual CRuntimeClass* GetRuntimeClass() const
	{
		return NULL;
	}
	virtual ~CObject() {}
protected:
	CObject() {}
};

char CObject::lpszClassName[] = "CObject"; //  IMPLEMENT_CLASSNAME(CObject);
CRuntimeClass CObject::classCObject = { "CObject", sizeof(CObject), NULL }; 

class Mgr
{
public:
	
	std::queue<CObject*>  m_StaticQueue;
	std::queue<CObject*>  m_UserQueue;

	void Create(CRuntimeClass* pRTC)
	{
		for (int iQueue = 0; iQueue < 1000; iQueue++) {
			CObject* pObj = pRTC->CreateObject();
			m_StaticQueue.push(pObj);
		}
	}

	CObject* CreateUser()
	{
		CObject* User = (CObject*)m_StaticQueue.front();
		m_UserQueue.push(User);
		return User;
	}
};

Mgr g_mgr;

//이 위는 라이브러리에 있는 클래스
//----------------------------------------------------------------------------------//
//이 아래는 프로그램 코드


class CUser : public CObject
{
public:
	DECLARE_CLASSNAME;		  /*static char lpszClassName[];            */
	DECLARE_DYNCREATE;		  /*static CObject* CreateObject();         */
	DECLARE_DYNCLASS_CREATE;  /*CRuntimeClass* GetRuntimeClass() const; */
	DECLARE_DYNAMIC(CUser);	  /*static CRuntimeClass classCUser;        */ 
protected:
	CUser() {}
};

IMPLEMENT_CLASSNAME(CUser);		   /*char CUser::lpszClassName[] = ("CUser");                                           */
IMPLEMENT_DYNCREATE(CUser);		   /*CObject* CUser::CreateObject() { return new CUser; }                               */
IMPLEMENT_DYNCLASS_CREATE(CUser);  /*CRuntimeClass* CUser::GetRuntimeClass() const { return &classCUser; }              */
IMPLEMENT_DYNAMIC(CUser);		   /*CRuntimeClass CUser::classCUser = { "CUser", sizeof(CUser), CUser::CreateObject }; */

class test : public CObject
{
public:
	DECLARE_CLASSNAME;		  /*static char lpszClassName[];            */
	DECLARE_DYNCREATE;		  /*static CObject* CreateObject();         */
	DECLARE_DYNCLASS_CREATE;  /*CRuntimeClass* GetRuntimeClass() const; */
	DECLARE_DYNAMIC(test);	  /*static CRuntimeClass classCUser;        */
protected:
	test() {}
};

IMPLEMENT_CLASSNAME(test);		   /*char CUser::lpszClassName[] = ("CUser");                                           */
IMPLEMENT_DYNCREATE(test);		   /*CObject* CUser::CreateObject() { return new CUser; }                               */
IMPLEMENT_DYNCLASS_CREATE(test);  /*CRuntimeClass* CUser::GetRuntimeClass() const { return &classCUser; }              */
IMPLEMENT_DYNAMIC(test);		   /*CRuntimeClass CUser::classCUser = { "CUser", sizeof(CUser), CUser::CreateObject }; */


int main()
{
	CRuntimeClass* pRTCMyClass = RUNTIME_CLASS(CUser);
	g_mgr.Create(pRTCMyClass);

	//CRuntimeClass* pRTCMyClass = &CUser::classCUser; //RUNTIME_CLASS(CUser);
	//CObject* p = pRTCMyClass->CreateObject();

	g_mgr.CreateUser();
	g_mgr.CreateUser();
	g_mgr.CreateUser();

	test* pPoint;
	CUser* pCUser;

	for (int i = 0; i < 2; i++) {
		pPoint = (test*)(g_mgr.m_UserQueue.front());
		std::cout << pPoint->lpszClassName << std::endl;
		g_mgr.m_UserQueue.pop();
		//delete (CUser*)(CUser*)(g_mgr.m_UserQueue.front());
	}

	pCUser = (CUser*)(g_mgr.m_UserQueue.front());
	std::cout << pCUser->lpszClassName << std::endl;
	g_mgr.m_UserQueue.pop();

}
