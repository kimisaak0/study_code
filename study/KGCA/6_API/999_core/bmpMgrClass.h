#pragma once
#include "bmpClass.h"

struct Cache
{
	int        iKey;
	T_STR      name;
	bmpClass*  m_pBmp;
};

class bmpMgrClass : public singletonPattern<bmpMgrClass>
{
	friend class singletonPattern<bmpMgrClass>;

	std::map<int, bmpClass*> m_mapList;
	std::list<Cache> m_listCache;
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

#define I_bmpMgr bmpMgrClass::GetInstance()