#include "PrototypeHeader.h"

class MazeFactory
{
public:
	MazeFactory() {}

public:
	virtual Maze* MakeMaze() const { return new Maze; }
	virtual Wall* MakeWall() const { return new Wall; }
	virtual Room* MakeRoom(int n) const { return new Room(n); }
	virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }

public:
	virtual ~MazeFactory() {}
};

class MazePrototypeFactory : public MazeFactory
{
private:
	Maze* m_ProtoMaze;
	Room* m_ProtoRoom;
	Wall* m_ProtoWall;
	Door* m_ProtoDoor;

public:
	MazePrototypeFactory(Maze* m, Wall* w, Room* r, Door* d)
	{
		m_ProtoMaze = m;
		m_ProtoWall = w;
		m_ProtoRoom = r;
		m_ProtoDoor = d;
	}

public:
	virtual Wall* MakeWall() 
	{ 
		//원형으로 생성.
		return m_ProtoWall->Clone(); 
	}

	virtual Door* MakeDoor(Room* r1, Room* r2)
	{
		//원형으로 생성.
		Door* door = m_ProtoDoor->Clone();
		door->Initialize(r1, r2);
		return door;
	}

public:
	virtual ~MazePrototypeFactory() {}
};


//+싱글톤
class MazeGame
{
private:
	static MazeGame* m_pInstance;

public:
	static MazeGame* Instance()	{
		if (m_pInstance == nullptr) {
			m_pInstance = new MazeGame;
		}

		return m_pInstance;
	}


protected:
	MazeGame() {}

public:
	Maze * CreateMaze(MazePrototypeFactory* fc)
	{
		Maze* aMaze = fc->MakeMaze();
		Room* r1 = fc->MakeRoom(1);
		aMaze->AddRoom(r1);
		Room* r2 = fc->MakeRoom(2);
		aMaze->AddRoom(r2);
		Door* theDoor = fc->MakeDoor(r1, r2);

		r1->setSide(north, fc->MakeWall());
		r1->setSide(east, theDoor);
		r1->setSide(south, fc->MakeWall());
		r1->setSide(west, fc->MakeWall());

		r2->setSide(north, fc->MakeWall());
		r2->setSide(east, fc->MakeWall());
		r2->setSide(south, fc->MakeWall());
		r2->setSide(west, theDoor);
		return aMaze;
	}

public:
	virtual ~MazeGame() {}
};

MazeGame* MazeGame::m_pInstance = nullptr;

int main()
{
	MazeGame* game = MazeGame::Instance();
	MazePrototypeFactory simpleMazeFactory(new Maze, new Wall, new Room, new Door);
	Maze* maze = game->CreateMaze(&simpleMazeFactory);
}