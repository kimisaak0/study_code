#pragma once

// 

#include <iostream>
#include <vector>
using std::vector;

enum Direction { north, east, south, west };

//미로의 모든 구성 요소들이 공통적으로 가져야 하는 기본 연산을 정의한 추상 클래스.
//미로의 모든 구성 요소들은 이 클래스를 상속받아서 만들어진다.
class MapSite {
public:
	//자식 클래스들이 이 연산을 재정의하도록 강제한다.
	//즉 인터페이스만 정의하고 실제 작동은 정의하지 않은 것.
	// Enter이므로 그 구성요소로 들어가려고 하는 연산이다.
	virtual void Enter() = 0;
};

//----------------기본적인 미로의 구성 요소들.  시작

//기본적인 방.
class Room : public MapSite
{
private:
	MapSite * m_pSides[4];       //방은 네개의 방향을 갖고 있고, 각 방향에는 미로의 다른 구성 요소가 올 수 있다.
	int      m_iRoomNum;        //방 번호

public:
	Room() {}
	// 방 번호를 지정하여 생성하는 생성자.
	Room(int RoomNum) { m_iRoomNum = RoomNum; }

public:
	void Enter() override {}   // 기본 연산 재정의 (를 해야한다..)

	MapSite* getSide(Direction dir) const { return m_pSides[dir]; } // 지정한 방향에 무엇이 있는지를 반환하는 메소드.

	void     setSide(Direction dir, MapSite* pMapSize)              // 지정한 방향에 무엇을 둘것인지를 결정하는 메소드.
	{
		m_pSides[dir] = pMapSize;
	}

public:
	~Room() {}
};

//기본적인 벽.
class Wall : public MapSite
{
public:
	Wall() {}

public:
	void Enter() override {}
	//원형 패턴에서 추가된 것. (핵심적인 부분)
	virtual Wall* Clone() { return new Wall(*this); }

public:
	~Wall() {}
};

//기본적인 문.
class Door : public MapSite
{
private:
	Room * m_pRoom1;         //연결된 방1
	Room* m_pRoom2;         //연결된 방2
	bool  m_bIsOpen;        //문이 열려있는지.

public:
	Door() {}
	//문은 두 방 사이에 있어야 한다. 
	Door(Room* a, Room* b) { m_pRoom1 = a; m_pRoom2 = b; }

	//원형을 제공받아 생성하는 생성자.
	Door(const Door& other)
	{
		m_pRoom1 = other.m_pRoom1;
		m_pRoom2 = other.m_pRoom2;
	}

public:
	//원형을 초기화하는 메소드
	virtual void Initialize(Room* r1, Room* r2)
	{
		m_pRoom1 = r1;
		m_pRoom2 = r2;
	}

	void Enter() override {} //현재 방에서 다음 방으로 이동하는 연산이 정의되어야 한다.
	Room* OtherSideFrom(Room* a) {} //현재 방을 넘겨주면 다음 방을 리턴해야 한다.

	//원형패턴에서 추가된 것.
	virtual Door* Clone() 
	{
		return new Door(*this);
	}

public:
	~Door() {}

};

//위의 구성 요소들을 복합하여 미로를 정의하는 클래스
class Maze //Product
{
private:
	vector<Room*> m_RoomList;  //방들을 벡터로 관리한다.

public:
	Maze() {}

public:
	void AddRoom(Room* room) { m_RoomList.push_back(room); }  //방을 추가하는 메소드

	Room* serchRoomNum(int num) const { return m_RoomList[num]; }  //방 번호로 방을 검색하는 메소드.

public:
	~Maze() {}
};


//추가된 구성요소들

//----------------마법에 걸린 방 구성 요소들. 시작
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


//---------------- 마법에 걸린 방 구성 요소들. 끝


//----------------폭탄이 설치된 방 구성 요소들. 시작

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
	//원형패턴
	virtual Wall* Clone() const
	{
		return new BombedWall(*this);
	}

public:
	~BombedWall() {};
};

//----------------폭탄이 설치된 방 구성 요소들. 끝