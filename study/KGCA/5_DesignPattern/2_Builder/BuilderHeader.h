#pragma once

//�� ������ ������ ���� �������� ���� �ٸ� ǥ�� ����� ���� �� �ִ�.
//��ü�� �����ϴ� �κ��� ���� �����ϰ�, �̸� ���������ν� ��ü ��ü�� �����ϸ�,
//������ ��ü�� ������ �ս��� �߰�, Ȯ���� �����ϰ� ��ȵ� �����̴�.

#include <iostream>
#include <vector>
using std::vector;

enum Direction { north, east, south, west };

class MapSite
{
	virtual void Enter() = 0;
};

class Room : public MapSite
{
private:
	MapSite * m_pSides[4];       //���� �װ��� ������ ���� �ְ�, �� ���⿡�� �̷��� �ٸ� ���� ��Ұ� �� �� �ִ�.
	int      m_iRoomNum;        //�� ��ȣ
	static int g_RoomCount;

public:
	void Enter() override {}   // �⺻ ���� ������ (�� �ؾ��Ѵ�..)

	MapSite* getSide(Direction dir) const { return m_pSides[dir]; } // ������ ���⿡ ������ �ִ����� ��ȯ�ϴ� �޼ҵ�.

	void     setSide(Direction dir, MapSite* pMapSize)              // ������ ���⿡ ������ �Ѱ������� �����ϴ� �޼ҵ�.
	{
		m_pSides[dir] = pMapSize;
	}

	int      getID() { return m_iRoomNum; }


public:
	Room() 
	{
		m_iRoomNum = g_RoomCount++;
	} // �ڵ����� �� ��ȣ�� ���� �ؾ� �ϴ� ��Ȳ...

	//Room(int RoomNum) { m_iRoomNum = RoomNum; }  // �� ��ȣ�� �����Ͽ� �����ϴ� ������.

	~Room() {}
};

int Room::g_RoomCount = 0;

//�⺻���� ��.
class Wall : public MapSite
{
public:
	void Enter() override {}

public:
	Wall() {}
	~Wall() {}
};

//�⺻���� ��.
class Door : public MapSite
{
private:
	Room * m_pRoom1;         //����� ��1
	Room* m_pRoom2;         //����� ��2
	bool  m_bIsOpen;        //���� �����ִ���.

public:
	void Enter() override {} //���� �濡�� ���� ������ �̵��ϴ� ������ ���ǵǾ�� �Ѵ�.
	Room* OtherSideFrom(Room* a) {} //���� ���� �Ѱ��ָ� ���� ���� �����ؾ� �Ѵ�.

public:
	//Door() {}

	//���� �� �� ���̿� �־�� �Ѵ�. 
	Door(Room* a, Room* b) { m_pRoom1 = a; m_pRoom2 = b; }

	~Door() {}

};

//���� ���� ��ҵ��� �����Ͽ� �̷θ� �����ϴ� Ŭ����
class Maze //Product
{
private:
	vector<Room*> m_RoomList;  //����� ���ͷ� �����Ѵ�.


public:
	void AddRoom(Room* room) { m_RoomList.push_back(room); }  //���� �߰��ϴ� �޼ҵ�
	Room* serchRoomNum(int num) const {
		for (int i = 0; i < m_RoomList.size(); i++) {
			if (m_RoomList[i]->getID() == num) {
				return m_RoomList[i];
			}
		}
	}  //�� ��ȣ�� ���� �˻��ϴ� �޼ҵ�.

public:
	Maze() {}
	~Maze() {}
};