#include "FMHeader.h"
#include <conio.h>

//���丮 �޼��� ������ �߰��Ǹ� : 
// ��, ��, ���� �����ϱ� ���ؼ� �����ڸ� �̿����� �ʰ� ���� �Լ��� ȣ���ϵ��� �����Ǿ� �ִٸ�,
// �� ���� �Լ��� ���� ������ �پ��� ������� ������ �� �ִ�.

class MazeGameFM //���Ĵٵ� ����
{
public:
	
	//�̰͵��� ���丮 �޼����.
	virtual Maze* MakeMaze() { return new Maze; }
	virtual Room* MakeRoom(int n) { return new Room(n); }
	virtual Wall* MakeWall() { return new Wall; }
	virtual Door* MakeDoor(Room* r1, Room* r2) { return new Door(r1, r2); }

	virtual Maze * CreateMaze()
	{
		Maze* aMaze = MakeMaze();
		Room* r1 = MakeRoom(1);
		Room* r2 = MakeRoom(2);
		Door* theDoor = MakeDoor(r1, r2);

		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->setSide(north, MakeWall());
		r1->setSide(east, theDoor);
		r1->setSide(south, MakeWall());
		r1->setSide(west, MakeWall());

		r2->setSide(north, MakeWall());
		r2->setSide(east, MakeWall());
		r2->setSide(south, MakeWall());
		r2->setSide(west, theDoor);

		return aMaze;
	}
};


//������ ���丮 �޼������ �������ߴ�.
class MazeGameFM_Bombed : public MazeGameFM
{
public:
	Wall* MakeWall() override { return new BombedWall; }
	Room* MakeRoom(int n) override { return new RoomWithABomb(n); }
	Door* MakeDoor(Room* r1, Room* r2) { return new DoorWithABomb(r1, r2); }
};

class MazeGameFM_Encanted : public MazeGameFM
{
protected:
	Spell * CastSpell() { return nullptr; }

public:
	Room* MakeRoom(int n) override { return new EnchantedRoom(n, CastSpell()); }
	Door* MakeDoor(Room* r1, Room* r2) override { return new DoorNeedingSpell(r1, r2); }
};


int main()
{
	MazeGameFM mg;
	Maze* pMaze1 = mg.CreateMaze();

	MazeGameFM_Bombed bombed_mg;
	Maze* pMaze2 = mg.CreateMaze();

	MazeGameFM_Encanted Enchanted_mg;
	Maze* pMaze3 = mg.CreateMaze();
}