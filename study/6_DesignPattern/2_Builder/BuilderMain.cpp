#include "BuilderHeader.h"

//���� ������ ���Ǹ� : 
// �����ϰ��� �ϴ� �̷ο� ��, ��, ���� �߰��ϴ� ������ ����ؼ� ���ο� �̷θ� ���� �� �ִ� ��ü�� �Ѱܹ޴´ٸ�,
// �̷θ� ����� ����� ������ �� ��ü�� ����� ���ؼ� �ذ��� �� �ִ�.

//�ٽ��� ������ �߰��ϴ� ������ �������� �ϰ�, ���Ϳ����� �̸� �����ϱ⸸ �ؼ� �̷θ� ���� �� �ִٴ� ���̴�.

//���Ͱ� ����ϱ� ���� ���� �������̽�
class MazeBuilder //Builder (�߻� Ŭ���� == �������̽�)
{
public:
	//���������Լ��� �ƴϹǷ� �ʿ��� ���길 �������ϸ� �ȴ�.
	virtual void BuildMaze() {}
	virtual int BuildRoom() { return 0; }
	virtual void BuildDoor(int from, int to) {}
	virtual Maze* GetMaze() { return nullptr; }

public:
	MazeBuilder() {}
};


//�⺻���� �̷θ� ����� ���� 
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

	//���� å�� ������ ���� ID�� ���� �Ű������� �ְ� �Ǿ��־�����,
	//���ļ� ���� ������ ����� ������ ���� ������ �� �ڵ����� �����ǰ� �Ͽ���.
	int BuildRoom() override
	{
			Room* room = new Room(); //���� ����
			room->setSide(north, new Wall);
			room->setSide(south, new Wall);
			room->setSide(east, new Wall);
			room->setSide(west, new Wall);
			m_pCurrentMaze->AddRoom(room);  //���� �̷ο� �߰�.

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
//���� ������ �־ ������ ���� �ٸ��� �ص�.

//��ź�� �ִ� ���� ����ϴ� ����
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

	//���� å�� ������ ���� ID�� ���� �Ű������� �ְ� �Ǿ��־�����,
	//���ļ� ���� ������ ����� ������ ���� ������ �� �ڵ����� �����ǰ� �Ͽ���.
	int BuildRoom() 
	{
		RoomWithABomb* room = new RoomWithABomb(); //���� ����
		room->setSide(north, new Wall);
		room->setSide(south, new Wall);
		room->setSide(east, new Wall);
		room->setSide(west, new Wall);
		m_pCurrentMaze->AddRoom(room);  //���� �̷ο� �߰�.

		return room->getID();
	}

	//���⿡�� ��ź�� �ִ� ��� ���� ���� ��� ���� �� �ְ� �Ϸ��� �׷��� �������̽��� �����, ���� ���Ϳ��� ����ؾ� �Ѵ�.

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


//���Ͱ� ��� ��� ���� ������� ���� ����.
//�̷θ� ���� ��ȯ���� ����. (�ε� �ϰ� �ߴ�.)

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

		Room* room = new Room(); //���� ����
		room->setSide(north, new Wall);
		room->setSide(south, new Wall);
		room->setSide(east, new Wall);
		room->setSide(west, new Wall);
		m_pCurrentMaze->AddRoom(room);  //���� �̷ο� �߰�.

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

		std::cout << "�� ���� : " << m_iRoomCount << std::endl;
		std::cout << "�� ���� : " << m_iDoorCount << std::endl;
	}

	Maze* GetMaze() override
	{
		return m_pCurrentMaze;
	}

public:
	~CountingMazeBuilder() {}
};


//���� Ŭ������ �ν��Ͻ��� �Ű������� �޾� �̷θ� �����ϴ� Ŭ����. 
//<����>�� ���� ���� ����.
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
		//int r4... (��û ���ٰ� ġ��)
		builder.BuildDoor(r1_id, r2_id);
		builder.BuildDoor(r1_id, r3_id);
		// builder.BuildDoor(r1_id, ... (��û ���ٰ� ġ��)

		//�̷� ������� ��û ������ �̷ε� ������ �� �ִٴ� ��.

		return builder.GetMaze();
	}
};

//�׽�Ʈ!

int main() 
{
	Maze* maze;
	MazeGameBD mg;

	//� ������ ����ϴ°��� ������ � �Լ��� ����ϴ��Ŀ� ���� ��������� �̷ΰ� �ٸ���.
	//(�����غ��� ���� �Լ��� ������ ��ũ����ȭ �ϴ°� ������ ����.)
	
	//�⺻!
	StandardMazeBuilder standard;
	mg.CreateMaze(standard);
	maze = standard.GetMaze();

	//��ź!
	BombMazeBuilder bomb;
	mg.CreateMaze(bomb);
	maze = standard.GetMaze();

	//�� ���Ͱ� �����ϴ� ���� ������ �̷��� ������ ����.
	int door;
	int room;

	CountingMazeBuilder counting;
	mg.CreateMaze(counting);
	counting.GetCounts(room, door);
	maze = standard.GetMaze();

	_getch();
}
