#pragma once

// AF�� ��ü�� ������ ������ ������ ��ǰ���� ���ϴ� ��ü�� �����ϱ� ���� ������ ������ �˻��� �ʿ䰡 ����.
// ���� ���ο� ��ǰ���� �����ҷ��� �� ��� ���� �ҽ��ڵ�ʹ� ���������� ���ο� ��ǰ���� �߰��ϴ� ���� �����ϴ�.

// �� ���������� ���� �ٸ� ������ ���� ����� ���丮�� ����µ� ����� �� �ִ�.

#include <iostream>
#include <vector>
using std::vector;

enum Direction {north, east, south, west};

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
	MapSite* m_pSides[4];       //���� �װ��� ������ ���� �ְ�, �� ���⿡�� �̷��� �ٸ� ���� ��Ұ� �� �� �ִ�.
	int      m_iRoomNum;        //�� ��ȣ

public:
	void Enter() override {}   // �⺻ ���� ������ (�� �ؾ��Ѵ�..)

	MapSite* getSide(Direction dir) const { return m_pSides[dir]; } // ������ ���⿡ ������ �ִ����� ��ȯ�ϴ� �޼ҵ�.

	void     setSide(Direction dir, MapSite* pMapSize)              // ������ ���⿡ ������ �Ѱ������� �����ϴ� �޼ҵ�.
	{
		m_pSides[dir] = pMapSize;
	}

public:
//	Room() {} // �ڵ����� �� ��ȣ�� ���� �� ���� ���� ���̴�.
	Room(int RoomNum) {	m_iRoomNum = RoomNum;}  // �� ��ȣ�� �����Ͽ� �����ϴ� ������.

	~Room() {}
};

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
	Room* m_pRoom1;         //����� ��1
	Room* m_pRoom2;         //����� ��2
	bool  m_bIsOpen;        //���� �����ִ���.

public:
	void Enter() override {} //���� �濡�� ���� ������ �̵��ϴ� ������ ���ǵǾ�� �Ѵ�.
	Room* OtherSideFrom(Room* a) {} //���� ���� �Ѱ��ָ� ���� ���� �����ؾ� �Ѵ�.

public:
	//Door() {}
	
	//���� �� �� ���̿� �־�� �Ѵ�. 
	Door(Room* a, Room* b) {m_pRoom1 = a; m_pRoom2 = b;	} 

	~Door() {}

};

//���� ���� ��ҵ��� �����Ͽ� �̷θ� �����ϴ� Ŭ����
class Maze
{
private:
	vector<Room*> m_RoomList;  //����� ���ͷ� �����Ѵ�.
	
public:
	void AddRoom(Room* room) { m_RoomList.push_back(room); }  //���� �߰��ϴ� �޼ҵ�
	Room* Roomnum(int num) const { return m_RoomList[num]; }  //�� ��ȣ�� ���� �˻��ϴ� �޼ҵ�.

public:
	Maze() {}
	~Maze() {}
};

//----------------�⺻���� �̷��� ���� ��ҵ�.  ��



//----------------������ �ɸ� �� ���� ��ҵ�. ����
class Spell {
public:
	Spell() {}
	~Spell() {}
};

class EnchantedRoom : public Room
{
public:
	EnchantedRoom(int n, Spell* sp) : Room(n) {}
};

class DoorNeedingSpell : public Door
{
public:
	DoorNeedingSpell(Room* r1, Room* r2) : Door(r1, r2) {}
};


//---------------- ������ �ɸ� �� ���� ��ҵ�. ��


//----------------��ź�� ��ġ�� �� ���� ��ҵ�. ����

class RoomWithABomb : public Room
{
public:
	RoomWithABomb(int n) : Room(n) {}
};

class DoorWithABomb : public Door
{
public:
	DoorWithABomb(Room* r1, Room* r2) : Door(r1,r2) {}

};

//----------------��ź�� ��ġ�� �� ���� ��ҵ�. ��