#include "Dog.h"
#include "JumpingCat.h"

//매개변수를 부모클래스의 참조나 포인터로 받으면 자식 클래스를 다 받을 수 있다.
void temp(Animal& ani)
{
	ani.printSpeed();
}

void temp1(Animal* ani)
{
	ani->printSpeed();
}

//추상클래스를 매개변수로 사용할 수 없다.
//void temp2(Animal ani)
//{
//	ani.printSpeed();
//}


int main()
{
	//추상 클래스로는 객체를 만들 수 없다.
	//Animal ani;

	Animal* ani[3];
	ani[0] = new Dog;
	ani[1] = new Cat;
	ani[2] = new JumpingCat;

	//부모 클래스의 포인터로 자식 클래스를 가리켜서 사용하기 
	for (int iCnt = 0; iCnt < 3; iCnt++) {
		ani[iCnt]->printName();
		ani[iCnt]->speak();
		cout << ani[iCnt]->walk(10) << endl;
		
		//참조를 받는 함수에 포인터를 쓸 수 없다.
		//temp(ani[iCnt]);

		temp1(ani[iCnt]);
	}

	//부모 클래스의 포인터로 자식 클래스의 멤버 함수를 호출할 수는 없다.
	//ani[0]->bite();
	//ani[1]->claw();
	
	//하향 형변환을 하면 가능하다.
	Dog* ani_0 = dynamic_cast<Dog*> (ani[0]);
	ani_0->bite();
	
	Cat c;
	temp(c);

	JumpingCat jc;
	temp1(&jc);
}