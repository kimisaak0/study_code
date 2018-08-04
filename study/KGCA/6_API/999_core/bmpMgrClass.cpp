#include "bmpMgrClass.h"



bmpMgrClass::bmpMgrClass()
{
	m_iIndex = 0;
}

void       bmpMgrClass::addCache(int iKey, T_STR name, bmpClass* pData)
{
	Cache cache;
	cache.iKey = iKey;
	cache.name = name;
	cache.m_pBmp = pData;

	if (m_listCache.size() >= 3) {
		m_listCache.pop_front();
	}

	m_listCache.push_back(cache);
}


int        bmpMgrClass::getCache(T_STR szName)
{
	std::list<Cache>::iterator iter;

	for (iter = m_listCache.begin(); iter != m_listCache.end(); iter++) {
		Cache& cache = *iter;
		if (cache.name == szName) {
			return cache.iKey;
		}
	}
	return -1;
}

bmpClass*  bmpMgrClass::getCache(int iKey)
{
	std::list<Cache>::iterator iter;

	for (iter = m_listCache.begin(); iter != m_listCache.end(); iter++) {
		Cache& cache = *iter;
		if (cache.iKey == iKey) {
			return cache.m_pBmp;
		}
	}
	return nullptr;
}

bmpClass*  bmpMgrClass::getPtr(int iKey)
{
	bmpClass* pBmp = getCache(iKey);

	if (pBmp) {
		return pBmp;
	}

	std::map<int, bmpClass*>::iterator iter;
	iter = m_mapList.find(iKey);
	if (iter == m_mapList.end()) {
		return nullptr;
	}
	return (*iter).second;
}

int        bmpMgrClass::Load(T_STR szLoadFile)
{
	T_STR szName = szLoadFile;
	int iKey = getCache(szName);

	if (iKey > 0) {
		return iKey;
	}

	std::map<int, bmpClass*>::iterator iter;

	for (iter = m_mapList.begin(); iter != m_mapList.end(); iter++) {
		bmpClass* pBmp = (bmpClass*)(*iter).second;
		if (pBmp->m_szName == szName) {
			addCache((*iter).first, szName, pBmp);
			return (*iter).first;
		}
	}

	bmpClass* pBmp = new bmpClass;
	if (pBmp->Load(szLoadFile)) {
		m_mapList.insert(std::make_pair(++m_iIndex, pBmp));
		addCache(m_iIndex, szName, pBmp);
		return m_iIndex;
	}

	return -1;
}


bmpMgrClass::~bmpMgrClass()
{
}
