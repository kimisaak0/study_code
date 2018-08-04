#include "Car.h"

void swapObject1(Car c1, Car c2);
void swapObject2(Car* c1, Car* c2);
void swapObject3(Car& c1, Car& c2);
void swapObject4(Car* c1, Car& c2);

Car returnObject1();


int main()
{
	cout << "객체의 정적 생성과 동적 생성" << endl;
	Car myCar;							// 객체의 정적 생성 (기본 생성자로 초기화)
	myCar.print();						// 정적 생성된 객체의 메소드 호출
	Car* pCar = new Car(60, 3, "black");	// 객체의 동적 생성
	pCar->print();							// 동적 생성된 객체의 메소드 호출

	Car c1(0, 1, "blue");
	Car c2(100, 3, "red");
	c1.isFaster(&c2);		//정적 생성된 객체의 주소값을 받기 위해서 &연산자 사용
	myCar.isFaster(pCar);	//동적 생성된 객체는 &연산자가 필요하지 않음

	
	

	cout << endl << "일반 객체와 const 객체" << endl;
	SerialCar sc(0000);			//일반 객체
	const SerialCar csc(0001);	//const 객체
								
	//const 객체로는 public 멤버 변수의 값도 변경할 수 없다.
	sc.temp = 10;			
	//csc.temp = 10;		

	//const 객체로는 const 함수만 호출 가능하다.
	//cout << csc.getSpeed();		
	cout << csc.getSerial();
//	csc.print();


	cout << endl << "디폴트 대입 연산자에 의한 객체 대입" << endl;
	//객체끼리의 대입은 따로 연산자 재정의를 하지 않아도 디폴트 대입 연산자에 의해서 가능하다.
	c1 = myCar;
	c1.print();
	myCar.print();

	cout << endl << "객체를 함수의 매개변수로 전달하는 경우" << endl;
	cout << endl;
	swapObject1(c1, c2);
	cout << "swapObject1 밖에서 호출" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();

	cout << endl;
	swapObject2(&c1, &c2);
	cout << "swapObject2 밖에서 호출" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();

	cout << endl;
	swapObject3(c1, c2);
	cout << "swapObject3 밖에서 호출" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : "; 
	c2.print();

	cout << endl;
	swapObject4(&c1, c2);
	cout << "swapObject4 밖에서 호출" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();


	cout << endl << "임시 객체" << endl;

	string s1 = "temporary ";
	string s2 = "object";
	const char* sp = (s1 + s2).c_str();	// .c_str() : string의 첫번째 문자의 주소를 반환한다.
	cout << "sp : " << sp << endl;		// sp는 임시 객체의 시작 주소를 가지고 있으므로 이 문장에서는 이미 사라진 주소를 가지고 있는 셈이다.
	// 쓰레기 값이 출력됨

	string s3;
	s3 = s1 + s2;			// 대입 연산자는 임시객체의 값을 복사한다.
	sp = s3.c_str();		// 여기서는 사라진 임시 객체가 아니라 새롭게 생성된 s3의 주소를 가지고 출력하는 셈이다.
	cout << "sp : " << sp << endl;

	Car(10, 2, "wow");		// 명시적으로 생성한 임시객체. 이 문장이 끝나면 사라진다.

	cout << endl << "임시 객체를 참조자에 저장" << endl;
	//Car& rc = Car(10, 5, "rc");		// 컴파일 에러! 비const 참조에 대한 초기 값은 lvalue여야 합니다.
	{
		const Car& rc = Car(10, 5, "rc");	// 임시객체를 참조자로 저장. 참조자가 존재하는 동안에는 사라지지 않는다. (
		rc.print();
	}
	//rc.print(); //범위를 벗어나면 참조자도 소멸된다.

	Temp(3);					// 임시 객체를 생성할 때는 생성자가 호출된다.
	Temp tempC = Temp(5);		// 임시 객체를 객체 변수에 복사한다는 의미.	
	//(객체 변수라는 표현이 생소한데 그냥 그 객체를 받을 수 있는 공간이 만들어진 것으로 보임, 생성자 호출 X)

	cout << endl << "함수가 객체를 반환하는 경우" << endl;
	returnObject1().print();			// 반환된 임시 객체를 통해 멤버 함수 호출
	//임시 객체의 포인터나 참조를 반환하는 경우는 어차피 의미가 없으므로 생략.

	cout << endl << "정적 멤버 변수와 정적 멤버 함수" << endl;
	
	//정적 멤버 변수나 함수는 객체 생성 전에도 호출 가능
	cout << StaticClass::R << endl;
	StaticClass::showN();

	StaticClass sca;
	StaticClass scb;
	StaticClass scc;

	//정적 멤버 변수이므로 값은 모두 같다.
	sca.showN();
	scc.showN();

	//scope를 벗어난 변수도 사라지긴 하는데 아무래도 동적 할당, 해제 한 수를 세는게 일반적이다.
	StaticClass* scp = new StaticClass;
	StaticClass::showN();

	delete scp;
	StaticClass::showN();

	cout << endl << "객체 배열" << endl;
	
	//객체 배열 선언과 초기화 (생성자를 호출해서 초기값을 준다. 각각 다른 생성자를 사용할 수도 있다.)
	Car objArray[3] = { Car(1000,2,"obj"),Car(200) };
	
	objArray[0].print();
	objArray[1].print(); 
	objArray[2].print(); //초기값을 주지 않은 객체 배열의 멤버는 디폴트 생성자로 초기화 된다.

	//객체 배열을 이용한 멤버 함수 호출 
	cout << "objArray->speed : " << objArray->getSpeed() << endl;

	//객체 배열을 이용한 멤버 변수 접근
	objArray[1].pub = 1;
	cout << "(objArray+1)->pub : " << (objArray+1)->pub << endl;
	//+연산이 ->연산보다 먼저 실행되어야 하므로 괄호가 꼭 필요하다. 
	//*를 안 붙이는 이유는 아직 정리가 안되므로 패스
	

	cout << endl << "객체 배열과 포인터" << endl;
	//배열의 이름은 포인터이다.
	cout << objArray->getSpeed() << endl;
	cout << (objArray+1)->getSpeed() << endl;	//*()을 쓰지 않는다.


	

	cout << endl << "클래스와 클래스 간의 관계" << endl;
	useclass use, has_a;
	SerialCar is_a(0000);

	//사용을 하려면 포함을 하고 있을 수 밖에 없다.
	cout << "사용 관계(use) : ";
	use.useT();

	cout << "포함 관계(has-a) : ";
	has_a.useT();

	cout << "상속 관계(is-a) : ";
	cout << is_a.getSpeed();
}


//함수의 인자로 객체를 전달 할 수 있다. 
//물론 그냥 전달하면 call by value이므로 값이 복사된다.
//즉 실제 값은 변경되지 않는다.
void swapObject1(Car c1, Car c2)
{
	Car temp;
	temp = c1;
	c1 = c2;
	c2 = temp;

	cout << "swapObject1 안에서 호출" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();
}

//함수의 인자로 객체의 포인터도 전달 할 수 있다.
//포인터로 전달하면 주소가 전달되므로 call by reference이다.
//즉 실제 값을 변경할 수 있다.
//다만 *연산자를 사용하여야 하므로 조금 번거롭다.
void swapObject2(Car* c1, Car* c2)
{
	Car temp;
	temp = *c1;
	*c1 = *c2;
	*c2 = temp;

	cout << "swapObject2 안에서 호출" << endl;
	cout << "c1 : ";
	(*c1).print();
	cout << "c2 : ";
	(*c2).print();
}

//함수의 인자로 객체의 참조자를 전달 할 수 있다.
//참조자로 전달하면 call by reference이므로 값을 변경할 수 있다.
//포인터 변수를 만들지도 않고, 안에서 *연산자도 쓰지 않으므로 C++에서는 가장 많이 쓰이는 방식이다.
void swapObject3(Car& c1, Car& c2)
{
	Car temp;
	temp = c1;
	c1 = c2;
	c2 = temp;

	cout << "swapObject3 안에서 호출" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();
}

//참조자와 레퍼런스를 같이 쓸 수도 있다.
void swapObject4(Car* c1, Car& c2)
{
	Car temp;
	temp = *c1;
	*c1 = c2;
	c2 = temp;

	cout << "swapObject4 안에서 호출" << endl;
	cout << "c1 : ";
	(*c1).print();
	cout << "c2 : ";
	c2.print();
}

Car returnObject1()
{
	Car temp(100, 3, "ro1");
	return temp;
}
