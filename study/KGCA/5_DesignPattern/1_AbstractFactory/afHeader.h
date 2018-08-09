#pragma once

// AF�� ��ü�� ������ ������ ������ ��ǰ���� ���ϴ� ��ü�� �����ϱ� ���� ������ ������ �˻��� �ʿ䰡 ����.
// ���� ���ο� ��ǰ���� �����ҷ��� �� ��� ���� �ҽ��ڵ�ʹ� ���������� ���ο� ��ǰ���� �߰��ϴ� ���� �����ϴ�.

#include <iostream>
#include <vector>
using std::vector;

enum Direction {north, east, south, west};

class MapSite {
public:
	virtual void Enter() = 0;
};

class Room : public MapSite
{
private:
	MapSite* m_pSides[4];
	int      m_iRoomNum;

public:
	void Enter() override {}

	MapSite* getSide(Direction dir) const {}
	void     setSide(Direction dir, MapSite* pMapSize)
	{
		m_pSides[dir] = pMapSize;
	}

public:
	Room() {}

	Room(int RoomNum)
	{
		m_iRoomNum = RoomNum;
	}

	~Room() {}
};

 
class Wall : public MapSite
{
public:
	void Enter() override {}

public:
	Wall() {}
	~Wall() {}
};

class Door : public MapSite
{
private:
	Room* m_pRoom1;
	Room* m_pRoom2;
	bool  m_bIsOpen;

public:
	void Enter() override {}
	Room* OtherSideFrom(Room* a) {}

public:
	Door() {}

	Door(Room* a, Room* b) 
	{
		m_pRoom1 = a;
		m_pRoom2 = b;
	}

	~Door() {}

};

class Maze
{
public:
	vector<Room*> m_RoomList;
	
	void AddRoom(Room* room) { m_RoomList.push_back(room); }
	Room* Roomnum(int num) const { return m_RoomList[num]; }

public:
	Maze() {}
	~Maze() {}
};