#pragma once
#include "bmpClass.h"


struct bmpCache
{
	int        iKey;   //bmpID��
	T_STR      name;   //bmp�̸�
	bmpClass*  m_pBmp; //bmp������
};

//�Ŵ��� Ŭ�����̹Ƿ� �̱��� ������ ���.
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

