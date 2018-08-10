#pragma once

//이 패턴은 동일한 생성 절차에서 서로 다른 표현 결과를 만들 수 있다.
//객체를 구성하는 부분을 먼저 생성하고, 이를 조합함으로써 전체 객체를 생성하며,
//생성할 객체의 종류가 손쉽게 추가, 확장이 가능하게 고안된 패턴이다.

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
	MapSite * m_pSides[4];       //방은 네개의 방향을 갖고 있고, 각 방향에는 미로의 다른 구성 요소가 올 수 있다.
	int      m_iRoomNum;        //방 번호
	static int g_RoomCount;

public:
	void Enter() override {}   // 기본 연산 재정의 (를 해야한다..)

	MapSite* getSide(Direction dir) const { return m_pSides[dir]; } // 지정한 방향에 무엇이 있는지를 반환하는 메소드.

	void     setSide(Direction dir, MapSite* pMapSize)              // 지정한 방향에 무엇을 둘것인지를 결정하는 메소드.
	{
		m_pSides[dir] = pMapSize;
	}

	int      getID() { return m_iRoomNum; }


public:
	Room() 
	{
		m_iRoomNum = g_RoomCount++;
	} // 자동으로 방 번호를 갖게 해야 하는 상황...

	//Room(int RoomNum) { m_iRoomNum = RoomNum; }  // 방 번호를 지정하여 생성하는 생성자.

	~Room() {}
};

int Room::g_RoomCount = 0;

//기본적인 벽.
class Wall : public MapSite
{
public:
	void Enter() override {}

public:
	Wall() {}
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
	void Enter() override {} //현재 방에서 다음 방으로 이동하는 연산이 정의되어야 한다.
	Room* OtherSideFrom(Room* a) {} //현재 방을 넘겨주면 다음 방을 리턴해야 한다.

public:
	//Door() {}

	//문은 두 방 사이에 있어야 한다. 
	Door(Room* a, Room* b) { m_pRoom1 = a; m_pRoom2 = b; }

	~Door() {}

};

//위의 구성 요소들을 복합하여 미로를 정의하는 클래스
class Maze //Product
{
private:
	vector<Room*> m_RoomList;  //방들을 벡터로 관리한다.


public:
	void AddRoom(Room* room) { m_RoomList.push_back(room); }  //방을 추가하는 메소드
	Room* serchRoomNum(int num) const {
		for (int i = 0; i < m_RoomList.size(); i++) {
			if (m_RoomList[i]->getID() == num) {
				return m_RoomList[i];
			}
		}
	}  //방 번호로 방을 검색하는 메소드.

public:
	Maze() {}
	~Maze() {}
};