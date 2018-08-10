#include "afHeader.h"


//�̷��� ������ҵ��� �����ϴ� (�⺻) �߻� ���丮 Ŭ����
//�� Ŭ������ ��ȯ�ϴ� ������ Ŭ������ ���� ���ǰ� �̸� �ʿ��ϴ�.
class MazeFactory
{
public:
	virtual Maze* MakeMaze() const { return new Maze; }                              //�̷θ� �����.
	virtual Wall* MakeWall() const { return new Wall; }                              //���� �����.
	virtual Room* MakeRoom(int n) const { return new Room(n); }                      //���� �����.
	virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }    //���õ� �� �� ���̿� ���� �����.


public:
	MazeFactory() {}
	~MazeFactory() {}
};


//������ �ɸ� �̷θ� �����ϴ� �߻� ���丮 Ŭ����
//�̷θ� ����� �޼ҵ�� ���� ����� �޼ҵ�� �޶����� ���� ������ �׳� ��ӹ޾Ƽ� ����ϰ�
//�ٸ��� ���۵� ���� ����� �޼ҵ�� ���� �޼ҵ常 �������ߴ�.
class EnchantedMazeFactory : public MazeFactory
{
protected:
	Spell * CastSpell() const { return new Spell; }

public:

// �Ʒ��� �� �Լ��� �״�� ����.
//	virtual Maze* MakeMaze() const { return new Maze; }                              //�̷θ� �����.
//	virtual Wall* MakeWall() const { return new Wall; }                              //���� �����.

	//�� Ŭ�������� ����ϴ� ������ �ɸ� ��� ������ �ɸ� ���� ������ Ŭ������ ��ӹ޾� �����ǵ� Ŭ�����̴�.

	Room * MakeRoom(int n) const override                                            //������ �ɸ� ���� �����.
	{
		//roomŬ������ ��ӹ��� EnchantedRoomŬ������ �ν��Ͻ��� �����Ѵ�.
		return new EnchantedRoom(n, CastSpell());
	}


	Door* MakeDoor(Room* r1, Room* r2) const override                                //������ �ɸ� ���� �����.
	{
		//DoorŬ������ ��ӹ��� DoorNeedingSpellŬ������ �ν��Ͻ��� �����Ѵ�.
		return new DoorNeedingSpell(r1, r2);
	}


public:
	EnchantedMazeFactory() {}

};


//��ź�� ��ġ�� �̷ζ�� ġ��
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


//�̷θ� ����� Ŭ����.
//������ �̷θ� ����� �˰����� �����Ǿ� ���� �ʰ�,
//�׳� �ι� ���̿� ���� ����� �͸� �����Ǿ� �ִ�.
class MazeGame
{
	//���丮 �޼��� ������ �߰��Ǹ� : 
	// ��, ��, ���� �����ϱ� ���ؼ� �����ڸ� �̿����� �ʰ� ���� �Լ��� ȣ���ϵ��� �����Ǿ� �ִٸ�,
	// �� ���� �Լ��� ���� ������ �پ��� ������� ������ �� �ִ�.

	//�߻� ���丮 ������ �߰��Ǹ� :
	// ��, ��, ���� �����ϱ� ���� ���� ����� �˰� �ִ� ��ü�� �Ű� ������ �Ѱܹ��� �� �ִٸ�,
	// ���� ����� �ٲ� ������ ���ο� �Ű������� �Ѱܹ������ν� ������ ��ü�� ������ �޸��� �� �ִ�.

	//���� ������ �߰��Ǹ� : 
	// �����ϰ��� �ϴ� �̷ο� ��, ��, ���� �߰��ϴ� ������ ����ؼ� ���ο� �̷θ� ���� �� �ִ� ��ü�� �Ѱܹ޴´ٸ�,
	// �̷θ� ����� ����̳� ������ �� ��ü�� ����� ���ؼ� �ذ��� �� �ִ�.

	//���� ������ �߰��Ǹ� :
	// �̹� ���� �پ��� ��, ��, �� ��ü�� �Ű�����ȭ �صΰ� �̹� ���� ��ü�� �����ؼ� �̷ο� �߰��ϸ�, 
	// �̵� �ν��Ͻ��� ��ü�Ͽ� �̷��� ���� ����� ������ �� �ִ�.

public:
	//������ ������ ������� ���� ����
	//������1 : �ٸ� ���� ��Ҹ� �߰��ؼ� �̷θ� ����Ⱑ ��ƴ�.
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

	//�߻� Ŭ���� ������ ����ϴ� ����
	//� �߻� ���丮�� ����ϴ��Ŀ� ���� ���� �ٸ� ������ �̷θ� ���� �� �ִ�. 
	//������ �Ű������� �޴´ٰ� �����ϸ� �ȴ�.
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

	//�⺻ �׸�
	MazeGame mg1;
	MazeFactory* factory1 = new MazeFactory;
	Maze* pMaze1 = mg1.CreateMaze(factory1);

	//������ �ɸ� �̷� �׸�
	MazeGame mg2;
	MazeFactory* factory2 = new EnchantedMazeFactory;
	Maze* pMaze2 = mg2.CreateMaze(factory2);

	//��ź�� ��ġ�� �̷� �׸�
	MazeGame mg3;
	MazeFactory* factory3 = new BombedMazeFactory;
	Maze* pMaze3 = mg3.CreateMaze(factory3);
	
}