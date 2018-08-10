#include "afHeader.h"


//미로의 구성요소들을 생성하는 (기본) 추상 팩토리 클래스
//이 클래스가 반환하는 각각의 클래스에 대한 정의가 미리 필요하다.
class MazeFactory
{
public:
	virtual Maze* MakeMaze() const { return new Maze; }                              //미로를 만든다.
	virtual Wall* MakeWall() const { return new Wall; }                              //벽을 만든다.
	virtual Room* MakeRoom(int n) const { return new Room(n); }                      //방을 만든다.
	virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }    //선택된 두 방 사이에 문을 만든다.


public:
	MazeFactory() {}
	~MazeFactory() {}
};


//마법에 걸린 미로를 생성하는 추상 팩토리 클래스
//미로를 만드는 메소드와 벽을 만드는 메소드는 달라진게 없기 때문에 그냥 상속받아서 사용하고
//다르게 제작된 방을 만드는 메소드와 문을 메소드만 재정의했다.
class EnchantedMazeFactory : public MazeFactory
{
protected:
	Spell * CastSpell() const { return new Spell; }

public:

// 아래의 두 함수는 그대로 쓴다.
//	virtual Maze* MakeMaze() const { return new Maze; }                              //미로를 만든다.
//	virtual Wall* MakeWall() const { return new Wall; }                              //벽을 만든다.

	//이 클래스에서 사용하는 마법에 걸린 방과 마법에 걸린 문은 각각의 클래스를 상속받아 재정의된 클래스이다.

	Room * MakeRoom(int n) const override                                            //마법에 걸린 방을 만든다.
	{
		//room클래스를 상속받은 EnchantedRoom클래스의 인스턴스를 리턴한다.
		return new EnchantedRoom(n, CastSpell());
	}


	Door* MakeDoor(Room* r1, Room* r2) const override                                //마법에 걸린 문을 만든다.
	{
		//Door클래스를 상속받은 DoorNeedingSpell클래스의 인스턴스를 리턴한다.
		return new DoorNeedingSpell(r1, r2);
	}


public:
	EnchantedMazeFactory() {}

};


//폭탄이 설치된 미로라고 치면
class BombedMazeFactory : public MazeFactory
{
public:
	Room* MakeRoom(int n) const override
	{
		return new RoomWithABomb(n);
	}

	Door* MakeDoor(Room* r1, Room* r2) const override 
	{
		return new DoorWithABomb(r1, r2);
	}

public:
	BombedMazeFactory() {}
};


//미로를 만드는 클래스.
//복잡한 미로를 만드는 알고리즘은 구현되어 있지 않고,
//그냥 두방 사이에 문을 만드는 것만 구현되어 있다.
class MazeGame
{
	//팩토리 메서드 패턴이 추가되면 : 
	// 방, 벽, 문을 생성하기 위해서 생성자를 이용하지 않고 가상 함수를 호출하도록 구현되어 있다면,
	// 이 가상 함수의 실제 구현을 다양한 방법으로 변경할 수 있다.

	//추상 팩토리 패턴이 추가되면 :
	// 방, 벽, 문을 생성하기 위한 생성 방법을 알고 있는 객체를 매개 변수로 넘겨받을 수 있다면,
	// 생성 방법이 바뀔 때마다 새로운 매개변수를 넘겨받음으로써 생성할 객체의 유형을 달리할 수 있다.

	//빌터 패턴이 추가되면 : 
	// 생성하고자 하는 미로에 방, 문, 벽을 추가하는 연산을 사용해서 새로운 미로를 만들 수 있는 객체를 넘겨받는다면,
	// 미로를 만드는 방법이나 변경을 이 객체의 상속을 통해서 해결할 수 있다.

	//원형 패턴을 추가되면 :
	// 이미 만든 다양한 방, 문, 벽 객체를 매개변수화 해두고 이미 만든 객체를 복사해서 미로에 추가하면, 
	// 이들 인스턴스를 교체하여 미로의 복합 방법을 변경할 수 있다.

public:
	//디자인 패턴을 사용하지 않은 버전
	//문제점1 : 다른 구성 요소를 추가해서 미로를 만들기가 어렵다.
	Maze * CreateMaze()
	{
		Maze* aMaze = new Maze;
		Room* r1 = new Room(1);
		Room* r2 = new Room(2);
		Door* theDoor = new Door(r1, r2);
		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->setSide(north, new Wall);
		r1->setSide(east, theDoor);
		r1->setSide(south, new Wall);
		r1->setSide(west, new Wall);

		r2->setSide(north, new Wall);
		r2->setSide(east, new Wall);
		r2->setSide(south, new Wall);
		r2->setSide(west, theDoor);

		return aMaze;
	}

	//추상 클래스 패턴을 사용하는 버전
	//어떤 추상 팩토리를 사용하느냐에 따라 전혀 다른 컨셉의 미로를 만들 수 있다. 
	//컨셉을 매개변수로 받는다고 생각하면 된다.
	Maze* CreateMaze(MazeFactory* factory)
	{
		Maze* aMaze = factory->MakeMaze();
		Room* r1 = factory->MakeRoom(1);
		Room* r2 = factory->MakeRoom(2);
		Door* theDoor = factory->MakeDoor(r1, r2);
		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->setSide(north, factory->MakeWall());
		r1->setSide(east, theDoor);
		r1->setSide(south, factory->MakeWall());
		r1->setSide(west,  factory->MakeWall());

		r2->setSide(north, factory->MakeWall());
		r2->setSide(east, factory->MakeWall());
		r2->setSide(south, factory->MakeWall());
		r2->setSide(west, theDoor);
		return aMaze;
	}
};

int main()
{
	MazeGame mg;
	Maze* pMaze = mg.CreateMaze();

	//기본 테마
	MazeGame mg1;
	MazeFactory* factory1 = new MazeFactory;
	Maze* pMaze1 = mg1.CreateMaze(factory1);

	//마법이 걸린 미로 테마
	MazeGame mg2;
	MazeFactory* factory2 = new EnchantedMazeFactory;
	Maze* pMaze2 = mg2.CreateMaze(factory2);

	//폭탄이 설치된 미로 테마
	MazeGame mg3;
	MazeFactory* factory3 = new BombedMazeFactory;
	Maze* pMaze3 = mg3.CreateMaze(factory3);
	
}