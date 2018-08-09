#include "afHeader.h"

class MazeFactory
{
public:
	virtual Maze* MakeMaze() const { return new Maze; }
	virtual Wall* MakeWall() const { return new Wall; }
	virtual Room* MakeRoom(int n) const { return new Room(n); }
	virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }


public:
	MazeFactory() {}
	~MazeFactory() {}
};

class Spell {
public:
	Spell() {}
	~Spell() {}
};

class EnchantRoom : public Room
{
public:
	EnchantRoom(int n, Spell* sp) : Room(n) {}
};

class DoorNeedingSpell : public Door
{
public:
	DoorNeedingSpell(Room* r1, Room* r2) : Door(r1,r2) {}
};

class EnchantedMazeFactory : public MazeFactory
{
protected:
	Spell * CastSpell() const { return new Spell; }

public:
	Room* MakeRoom(int n) const override
	{
		return new EnchantRoom(n, CastSpell());
	}

	Door* MakeDoor(Room* r1, Room* r2) const override
	{
		return new DoorNeedingSpell(r1, r2);
	}


public:
	EnchantedMazeFactory() {}

};

class MazeGame
{
public:
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

	MazeGame mg1;
	MazeFactory* factory1 = new MazeFactory;
	Maze* pMaze1 = mg1.CreateMaze(factory1);

	MazeGame mg2;
	MazeFactory* factory2 = new EnchantedMazeFactory;
	Maze* pMaze2 = mg1.CreateMaze(factory2);
}