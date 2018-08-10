#include "BuilderHeader.h"

class MazeBuilder //Builder (추상 클래스)
{
public:
	virtual void BuildMaze() {}
	virtual int BuildRoom() { return 0; }
	virtual void BuildDoor(int from, int to) {}
	virtual Maze* GetMaze() { return nullptr; }

public:
	MazeBuilder() {}
};

class StandardMazeBuilder : public MazeBuilder //ConcreteBuilder
{
private:
	Maze * m_pCurrentMaze;

private:
	Direction CommonWall(Room* r1, Room* r2) 
	{
		return (Direction)(rand() % 4);
	}

public: 
	void BuildMaze() override 
	{
		m_pCurrentMaze = new Maze();
	}

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
	StandardMazeBuilder()
	{
		m_pCurrentMaze = nullptr;
	}
};

class createMaze //Director
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
};

int main() 
{
	Maze* maze;
	createMaze mg;
	//어떤 미로를 만들것인지.
	StandardMazeBuilder standard;

	mg.CreateMaze(standard);
	maze = standard.GetMaze();

}
