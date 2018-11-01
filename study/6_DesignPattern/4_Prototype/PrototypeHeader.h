#pragma once

// 

#include <iostream>
#include <vector>
using std::vector;

enum Direction { north, east, south, west };

//�̷��� ��� ���� ��ҵ��� ���������� ������ �ϴ� �⺻ ������ ������ �߻� Ŭ����.
//�̷��� ��� ���� ��ҵ��� �� Ŭ������ ��ӹ޾Ƽ� ���������.
class MapSite {
public:
	//�ڽ� Ŭ�������� �� ������ �������ϵ��� �����Ѵ�.
	//�� �������̽��� �����ϰ� ���� �۵��� �������� ���� ��.
	// Enter�̹Ƿ� �� ������ҷ� ������ �ϴ� �����̴�.
	virtual void Enter() = 0;
};

//----------------�⺻���� �̷��� ���� ��ҵ�.  ����

//�⺻���� ��.
class Room : public MapSite
{
private:
	MapSite * m_pSides[4];       //���� �װ��� ������ ���� �ְ�, �� ���⿡�� �̷��� �ٸ� ���� ��Ұ� �� �� �ִ�.
	int      m_iRoomNum;        //�� ��ȣ

public:
	Room() {}
	// �� ��ȣ�� �����Ͽ� �����ϴ� ������.
	Room(int RoomNum) { m_iRoomNum = RoomNum; }

public:
	void Enter() override {}   // �⺻ ���� ������ (�� �ؾ��Ѵ�..)

	MapSite* getSide(Direction dir) const { return m_pSides[dir]; } // ������ ���⿡ ������ �ִ����� ��ȯ�ϴ� �޼ҵ�.

	void     setSide(Direction dir, MapSite* pMapSize)              // ������ ���⿡ ������ �Ѱ������� �����ϴ� �޼ҵ�.
	{
		m_pSides[dir] = pMapSize;
	}

public:
	~Room() {}
};

//�⺻���� ��.
class Wall : public MapSite
{
public:
	Wall() {}

public:
	void Enter() override {}
	//���� ���Ͽ��� �߰��� ��. (�ٽ����� �κ�)
	virtual Wall* Clone() { return new Wall(*this); }

public:
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
	Door() {}
	//���� �� �� ���̿� �־�� �Ѵ�. 
	Door(Room* a, Room* b) { m_pRoom1 = a; m_pRoom2 = b; }

	//������ �����޾� �����ϴ� ������.
	Door(const Door& other)
	{
		m_pRoom1 = other.m_pRoom1;
		m_pRoom2 = other.m_pRoom2;
	}

public:
	//������ �ʱ�ȭ�ϴ� �޼ҵ�
	virtual void Initialize(Room* r1, Room* r2)
	{
		m_pRoom1 = r1;
		m_pRoom2 = r2;
	}

	void Enter() override {} //���� �濡�� ���� ������ �̵��ϴ� ������ ���ǵǾ�� �Ѵ�.
	Room* OtherSideFrom(Room* a) {} //���� ���� �Ѱ��ָ� ���� ���� �����ؾ� �Ѵ�.

	//�������Ͽ��� �߰��� ��.
	virtual Door* Clone() 
	{
		return new Door(*this);
	}

public:
	~Door() {}

};

//���� ���� ��ҵ��� �����Ͽ� �̷θ� �����ϴ� Ŭ����
class Maze //Product
{
private:
	vector<Room*> m_RoomList;  //����� ���ͷ� �����Ѵ�.

public:
	Maze() {}

public:
	void AddRoom(Room* room) { m_RoomList.push_back(room); }  //���� �߰��ϴ� �޼ҵ�

	Room* serchRoomNum(int num) const { return m_RoomList[num]; }  //�� ��ȣ�� ���� �˻��ϴ� �޼ҵ�.

public:
	~Maze() {}
};


//�߰��� ������ҵ�

//----------------������ �ɸ� �� ���� ��ҵ�. ����
//class Spell {
//public:
//	Spell() {}
//	~Spell() {}
//};
//
//class EnchantedRoom : public Room
//{
//public:
//	EnchantedRoom(int n, Spell* sp) : Room(n) {}
//};
//
//class DoorNeedingSpell : public Door
//{
//public:
//	DoorNeedingSpell(Room* r1, Room* r2) : Door(r1, r2) {}
//};


//---------------- ������ �ɸ� �� ���� ��ҵ�. ��


//----------------��ź�� ��ġ�� �� ���� ��ҵ�. ����

//class RoomWithABomb : public Room
//{
//public:
//	RoomWithABomb(int n) : Room(n) {}
//};
//
//class DoorWithABomb : public Door
//{
//public:
//	DoorWithABomb(Room* r1, Room* r2) : Door(r1, r2) {}
//};

class BombedWall : public Wall
{
private:
	bool m_bBomb;

public:
	BombedWall() {};
	BombedWall(const BombedWall& other) : Wall(other)
	{
		m_bBomb = other.m_bBomb;
	}

public:
	//��������
	virtual Wall* Clone() const
	{
		return new BombedWall(*this);
	}

public:
	~BombedWall() {};
};

//----------------��ź�� ��ġ�� �� ���� ��ҵ�. ��