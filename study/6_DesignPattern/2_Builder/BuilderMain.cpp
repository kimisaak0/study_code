#include "BuilderHeader.h"

//빌터 패턴이 사용되면 : 
// 생성하고자 하는 미로에 방, 문, 벽을 추가하는 연산을 사용해서 새로운 미로를 만들 수 있는 객체를 넘겨받는다면,
// 미로를 만드는 방법의 변경을 이 객체의 상속을 통해서 해결할 수 있다.

//핵심은 각각을 추가하는 연산은 빌더에서 하고, 디렉터에서는 이를 조합하기만 해서 미로를 만들어낼 수 있다는 것이다.

//디렉터가 사용하기 위한 빌더 인터페이스
class MazeBuilder //Builder (추상 클래스 == 인터페이스)
{
public:
	//순수가상함수는 아니므로 필요한 연산만 재정의하면 된다.
	virtual void BuildMaze() {}
	virtual int BuildRoom() { return 0; }
	virtual void BuildDoor(int from, int to) {}
	virtual Maze* GetMaze() { return nullptr; }

public:
	MazeBuilder() {}
};


//기본적인 미로를 만드는 빌더 
class StandardMazeBuilder : public MazeBuilder //ConcreteBuilder
{
private:
	Maze * m_pCurrentMaze;

private:
	Direction CommonWall(Room* r1, Room* r2) {return (Direction)(rand() % 4); }

 
public:
	StandardMazeBuilder()
	{
		m_pCurrentMaze = nullptr;
	}

public:
	void BuildMaze() override
	{ 
		m_pCurrentMaze = new Maze(); 
	}

	//원래 책의 예제는 방의 ID를 직접 매개변수로 주게 되어있었지만,
	//겹쳐서 들어가면 문제가 생기기 때문에 방이 생성될 때 자동으로 지정되게 하였다.
	int BuildRoom() override
	{
			Room* room = new Room(); //방을 생성
			room->setSide(north, new Wall);
			room->setSide(south, new Wall);
			room->setSide(east, new Wall);
			room->setSide(west, new Wall);
			m_pCurrentMaze->AddRoom(room);  //방을 미로에 추가.

			return room->getID();
	}

	void BuildDoor(int from, int to) override 
	{
		Room* r1 = m_pCurrentMaze->serchRoomNum(from);
		Room* r2 = m_pCurrentMaze->serchRoomNum(to);
		Door* d = new Door(r1, r2);

		r1->setSide(CommonWall(r1, r2), d);
		r1->setSide(CommonWall(r2, r1), d);
	}

	Maze* GetMaze() override 
	{
		return m_pCurrentMaze; 
	}

public:
	~StandardMazeBuilder() 
	{
	}
};
//조금 문제가 있어서 예제랑 조금 다르게 해둠.

//폭탄이 있는 방을 사용하는 빌더
class BombMazeBuilder : public MazeBuilder //ConcreteBuilder
{
private:
	Maze * m_pCurrentMaze;

private:
	Direction CommonWall(Room* r1, Room* r2) { return (Direction)(rand() % 4); }


public:
	BombMazeBuilder()
	{
		m_pCurrentMaze = nullptr;
	}

public:
	void BuildMaze() override
	{
		m_pCurrentMaze = new Maze();
	}

	//원래 책의 예제는 방의 ID를 직접 매개변수로 주게 되어있었지만,
	//겹쳐서 들어가면 문제가 생기기 때문에 방이 생성될 때 자동으로 지정되게 하였다.
	int BuildRoom() 
	{
		RoomWithABomb* room = new RoomWithABomb(); //방을 생성
		room->setSide(north, new Wall);
		room->setSide(south, new Wall);
		room->setSide(east, new Wall);
		room->setSide(west, new Wall);
		m_pCurrentMaze->AddRoom(room);  //방을 미로에 추가.

		return room->getID();
	}

	//여기에서 폭탄이 있는 방과 없는 방을 모두 만들 수 있게 하려면 그러한 인터페이스를 만들고, 빌더 디렉터에서 사용해야 한다.

	void BuildDoor(int from, int to) override
	{
		Room* r1 = m_pCurrentMaze->serchRoomNum(from);
		Room* r2 = m_pCurrentMaze->serchRoomNum(to);
		Door* d = new Door(r1, r2);

		r1->setSide(CommonWall(r1, r2), d);
		r1->setSide(CommonWall(r2, r1), d);
	}

	Maze* GetMaze() override
	{
		return m_pCurrentMaze;
	}

public:
	~BombMazeBuilder()
	{
	}
};


//디렉터가 몇개의 방과 문을 만드는지 세는 빌더.
//미로를 만들어서 반환하진 않음. (인데 하게 했다.)

class CountingMazeBuilder : public MazeBuilder
{
private:
	Maze* m_pCurrentMaze;

	int m_iRoomCount;
	int m_iDoorCount;

private:
	Direction CommonWall(Room* r1, Room* r2) { return (Direction)(rand() % 4); }

public:
	CountingMazeBuilder() 
	{
		m_iRoomCount = 0;
		m_iDoorCount = 0;
	}

public:
	void BuildMaze() override
	{
		m_pCurrentMaze = new Maze();
	}

	int BuildRoom() override 
	{ 
		m_iRoomCount++;

		Room* room = new Room(); //방을 생성
		room->setSide(north, new Wall);
		room->setSide(south, new Wall);
		room->setSide(east, new Wall);
		room->setSide(west, new Wall);
		m_pCurrentMaze->AddRoom(room);  //방을 미로에 추가.

		return room->getID();
	}

	void BuildDoor(int from, int to) override 
	{
		m_iDoorCount++;

		Room* r1 = m_pCurrentMaze->serchRoomNum(from);
		Room* r2 = m_pCurrentMaze->serchRoomNum(to);
		Door* d = new Door(r1, r2);

		r1->setSide(CommonWall(r1, r2), d);
		r1->setSide(CommonWall(r2, r1), d);
	}

	void GetCounts(int& room, int& door) 
	{
		room = m_iRoomCount;
		door = m_iDoorCount;

		std::cout << "방 갯수 : " << m_iRoomCount << std::endl;
		std::cout << "문 갯수 : " << m_iDoorCount << std::endl;
	}

	Maze* GetMaze() override
	{
		return m_pCurrentMaze;
	}

public:
	~CountingMazeBuilder() {}
};


//빌더 클래스의 인스턴스를 매개변수로 받아 미로를 생성하는 클래스. 
//<빌더>에 대한 디렉터 역할.
class MazeGameBD //Director
{
public:
	Maze * CreateMaze(MazeBuilder& builder) 
	{
		builder.BuildMaze();
		int r1_id = builder.BuildRoom();
		int r2_id =builder.BuildRoom();
		builder.BuildDoor(r1_id, r2_id);

		return builder.GetMaze();
	}

	Maze* CreateComplexMaze(MazeBuilder& builder)
	{
		builder.BuildMaze();
		int r1_id = builder.BuildRoom();
		int r2_id = builder.BuildRoom();
		int r3_id = builder.BuildRoom();
		//int r4... (엄청 많다고 치자)
		builder.BuildDoor(r1_id, r2_id);
		builder.BuildDoor(r1_id, r3_id);
		// builder.BuildDoor(r1_id, ... (엄청 많다고 치자)

		//이런 방식으로 엄청 복잡한 미로도 생성할 수 있다는 뜻.

		return builder.GetMaze();
	}
};

//테스트!

int main() 
{
	Maze* maze;
	MazeGameBD mg;

	//어떤 빌더를 사용하는가와 디렉터의 어떤 함수를 사용하느냐에 따라서 만들어지는 미로가 다르다.
	//(생각해보면 디렉터 함수의 내용은 스크립터화 하는게 좋을것 같다.)
	
	//기본!
	StandardMazeBuilder standard;
	mg.CreateMaze(standard);
	maze = standard.GetMaze();

	//폭탄!
	BombMazeBuilder bomb;
	mg.CreateMaze(bomb);
	maze = standard.GetMaze();

	//이 디렉터가 생성하는 방의 갯수와 미로의 갯수를 센다.
	int door;
	int room;

	CountingMazeBuilder counting;
	mg.CreateMaze(counting);
	counting.GetCounts(room, door);
	maze = standard.GetMaze();

	_getch();
}
