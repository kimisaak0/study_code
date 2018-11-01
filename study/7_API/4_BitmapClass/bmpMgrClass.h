#pragma once
#include "bmpClass.h"


struct bmpCache
{
	int        iKey;   //bmpID값
	T_STR      name;   //bmp이름
	bmpClass*  m_pBmp; //bmp포인터
};

//매니저 클래스이므로 싱글톤 패턴을 상속.
class bmpMgrClass : public singletonPattern<bmpMgrClass>
{
	friend class singletonPattern<bmpMgrClass>;

	std::map<int, bmpClass*> m_mapList;   //
	std::list<bmpCache> m_listCache;      //
	int m_iIndex;

public:

	void       addCache(int iKey, T_STR name, bmpClass* pData);

	bmpClass*  getCache(int iKey);
	int        getCache(T_STR szName);

	bmpClass*  getPtr(int iKey);
	
	int        Load(T_STR szLoadFile);

protected:
	bmpMgrClass();

public:
	virtual ~bmpMgrClass();
};

