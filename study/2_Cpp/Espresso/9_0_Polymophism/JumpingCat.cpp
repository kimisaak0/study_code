#include "JumpingCat.h"

//오버라이딩 함수
void  JumpingCat::speak()
{
	cout << "grrrrrrr" << endl;
}

int   JumpingCat::walk(int here)
{
	//부모의 멤버 변수를 그대로 쓸 수 있다.
	return here + speed;
}

void  JumpingCat::printName()
{
	cout << name << endl;
}

//추가한 함수
void JumpingCat::jump()
{
	cout << "JumpingCat은 점프도 할 수 있다!" << endl;
}

JumpingCat::JumpingCat()
{
	//멤버 변수를 오버라이딩 하면 자식 클래스의 멤버 변수가 부모 클래스의 멤버 변수의 이름을 완전히 가리게된다.
	name = "점핑 캣!";
	//부모의 멤버 변수를 새롭게 초기화해서 그대로 쓸 수 있다.
	speed = 5;
}


JumpingCat::~JumpingCat()
{
}
