#include "Dog.h"
#include "JumpingCat.h"

//�Ű������� �θ�Ŭ������ ������ �����ͷ� ������ �ڽ� Ŭ������ �� ���� �� �ִ�.
void temp(Animal& ani)
{
	ani.printSpeed();
}

void temp1(Animal* ani)
{
	ani->printSpeed();
}

//�߻�Ŭ������ �Ű������� ����� �� ����.
//void temp2(Animal ani)
//{
//	ani.printSpeed();
//}


int main()
{
	//�߻� Ŭ�����δ� ��ü�� ���� �� ����.
	//Animal ani;

	Animal* ani[3];
	ani[0] = new Dog;
	ani[1] = new Cat;
	ani[2] = new JumpingCat;

	//�θ� Ŭ������ �����ͷ� �ڽ� Ŭ������ �����Ѽ� ����ϱ� 
	for (int iCnt = 0; iCnt < 3; iCnt++) {
		ani[iCnt]->printName();
		ani[iCnt]->speak();
		cout << ani[iCnt]->walk(10) << endl;
		
		//������ �޴� �Լ��� �����͸� �� �� ����.
		//temp(ani[iCnt]);

		temp1(ani[iCnt]);
	}

	//�θ� Ŭ������ �����ͷ� �ڽ� Ŭ������ ��� �Լ��� ȣ���� ���� ����.
	//ani[0]->bite();
	//ani[1]->claw();
	
	//���� ����ȯ�� �ϸ� �����ϴ�.
	Dog* ani_0 = dynamic_cast<Dog*> (ani[0]);
	ani_0->bite();
	
	Cat c;
	temp(c);

	JumpingCat jc;
	temp1(&jc);
}