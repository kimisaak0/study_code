#include "Car.h"

void swapObject1(Car c1, Car c2);
void swapObject2(Car* c1, Car* c2);
void swapObject3(Car& c1, Car& c2);
void swapObject4(Car* c1, Car& c2);

Car returnObject1();


int main()
{
	cout << "��ü�� ���� ������ ���� ����" << endl;
	Car myCar;							// ��ü�� ���� ���� (�⺻ �����ڷ� �ʱ�ȭ)
	myCar.print();						// ���� ������ ��ü�� �޼ҵ� ȣ��
	Car* pCar = new Car(60, 3, "black");	// ��ü�� ���� ����
	pCar->print();							// ���� ������ ��ü�� �޼ҵ� ȣ��

	Car c1(0, 1, "blue");
	Car c2(100, 3, "red");
	c1.isFaster(&c2);		//���� ������ ��ü�� �ּҰ��� �ޱ� ���ؼ� &������ ���
	myCar.isFaster(pCar);	//���� ������ ��ü�� &�����ڰ� �ʿ����� ����

	
	

	cout << endl << "�Ϲ� ��ü�� const ��ü" << endl;
	SerialCar sc(0000);			//�Ϲ� ��ü
	const SerialCar csc(0001);	//const ��ü
								
	//const ��ü�δ� public ��� ������ ���� ������ �� ����.
	sc.temp = 10;			
	//csc.temp = 10;		

	//const ��ü�δ� const �Լ��� ȣ�� �����ϴ�.
	//cout << csc.getSpeed();		
	cout << csc.getSerial();
//	csc.print();


	cout << endl << "����Ʈ ���� �����ڿ� ���� ��ü ����" << endl;
	//��ü������ ������ ���� ������ �����Ǹ� ���� �ʾƵ� ����Ʈ ���� �����ڿ� ���ؼ� �����ϴ�.
	c1 = myCar;
	c1.print();
	myCar.print();

	cout << endl << "��ü�� �Լ��� �Ű������� �����ϴ� ���" << endl;
	cout << endl;
	swapObject1(c1, c2);
	cout << "swapObject1 �ۿ��� ȣ��" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();

	cout << endl;
	swapObject2(&c1, &c2);
	cout << "swapObject2 �ۿ��� ȣ��" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();

	cout << endl;
	swapObject3(c1, c2);
	cout << "swapObject3 �ۿ��� ȣ��" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : "; 
	c2.print();

	cout << endl;
	swapObject4(&c1, c2);
	cout << "swapObject4 �ۿ��� ȣ��" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();


	cout << endl << "�ӽ� ��ü" << endl;

	string s1 = "temporary ";
	string s2 = "object";
	const char* sp = (s1 + s2).c_str();	// .c_str() : string�� ù��° ������ �ּҸ� ��ȯ�Ѵ�.
	cout << "sp : " << sp << endl;		// sp�� �ӽ� ��ü�� ���� �ּҸ� ������ �����Ƿ� �� ���忡���� �̹� ����� �ּҸ� ������ �ִ� ���̴�.
	// ������ ���� ��µ�

	string s3;
	s3 = s1 + s2;			// ���� �����ڴ� �ӽð�ü�� ���� �����Ѵ�.
	sp = s3.c_str();		// ���⼭�� ����� �ӽ� ��ü�� �ƴ϶� ���Ӱ� ������ s3�� �ּҸ� ������ ����ϴ� ���̴�.
	cout << "sp : " << sp << endl;

	Car(10, 2, "wow");		// ��������� ������ �ӽð�ü. �� ������ ������ �������.

	cout << endl << "�ӽ� ��ü�� �����ڿ� ����" << endl;
	//Car& rc = Car(10, 5, "rc");		// ������ ����! ��const ������ ���� �ʱ� ���� lvalue���� �մϴ�.
	{
		const Car& rc = Car(10, 5, "rc");	// �ӽð�ü�� �����ڷ� ����. �����ڰ� �����ϴ� ���ȿ��� ������� �ʴ´�. (
		rc.print();
	}
	//rc.print(); //������ ����� �����ڵ� �Ҹ�ȴ�.

	Temp(3);					// �ӽ� ��ü�� ������ ���� �����ڰ� ȣ��ȴ�.
	Temp tempC = Temp(5);		// �ӽ� ��ü�� ��ü ������ �����Ѵٴ� �ǹ�.	
	//(��ü ������� ǥ���� �����ѵ� �׳� �� ��ü�� ���� �� �ִ� ������ ������� ������ ����, ������ ȣ�� X)

	cout << endl << "�Լ��� ��ü�� ��ȯ�ϴ� ���" << endl;
	returnObject1().print();			// ��ȯ�� �ӽ� ��ü�� ���� ��� �Լ� ȣ��
	//�ӽ� ��ü�� �����ͳ� ������ ��ȯ�ϴ� ���� ������ �ǹ̰� �����Ƿ� ����.

	cout << endl << "���� ��� ������ ���� ��� �Լ�" << endl;
	
	//���� ��� ������ �Լ��� ��ü ���� ������ ȣ�� ����
	cout << StaticClass::R << endl;
	StaticClass::showN();

	StaticClass sca;
	StaticClass scb;
	StaticClass scc;

	//���� ��� �����̹Ƿ� ���� ��� ����.
	sca.showN();
	scc.showN();

	//scope�� ��� ������ ������� �ϴµ� �ƹ����� ���� �Ҵ�, ���� �� ���� ���°� �Ϲ����̴�.
	StaticClass* scp = new StaticClass;
	StaticClass::showN();

	delete scp;
	StaticClass::showN();

	cout << endl << "��ü �迭" << endl;
	
	//��ü �迭 ����� �ʱ�ȭ (�����ڸ� ȣ���ؼ� �ʱⰪ�� �ش�. ���� �ٸ� �����ڸ� ����� ���� �ִ�.)
	Car objArray[3] = { Car(1000,2,"obj"),Car(200) };
	
	objArray[0].print();
	objArray[1].print(); 
	objArray[2].print(); //�ʱⰪ�� ���� ���� ��ü �迭�� ����� ����Ʈ �����ڷ� �ʱ�ȭ �ȴ�.

	//��ü �迭�� �̿��� ��� �Լ� ȣ�� 
	cout << "objArray->speed : " << objArray->getSpeed() << endl;

	//��ü �迭�� �̿��� ��� ���� ����
	objArray[1].pub = 1;
	cout << "(objArray+1)->pub : " << (objArray+1)->pub << endl;
	//+������ ->���꺸�� ���� ����Ǿ�� �ϹǷ� ��ȣ�� �� �ʿ��ϴ�. 
	//*�� �� ���̴� ������ ���� ������ �ȵǹǷ� �н�
	

	cout << endl << "��ü �迭�� ������" << endl;
	//�迭�� �̸��� �������̴�.
	cout << objArray->getSpeed() << endl;
	cout << (objArray+1)->getSpeed() << endl;	//*()�� ���� �ʴ´�.


	

	cout << endl << "Ŭ������ Ŭ���� ���� ����" << endl;
	useclass use, has_a;
	SerialCar is_a(0000);

	//����� �Ϸ��� ������ �ϰ� ���� �� �ۿ� ����.
	cout << "��� ����(use) : ";
	use.useT();

	cout << "���� ����(has-a) : ";
	has_a.useT();

	cout << "��� ����(is-a) : ";
	cout << is_a.getSpeed();
}


//�Լ��� ���ڷ� ��ü�� ���� �� �� �ִ�. 
//���� �׳� �����ϸ� call by value�̹Ƿ� ���� ����ȴ�.
//�� ���� ���� ������� �ʴ´�.
void swapObject1(Car c1, Car c2)
{
	Car temp;
	temp = c1;
	c1 = c2;
	c2 = temp;

	cout << "swapObject1 �ȿ��� ȣ��" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();
}

//�Լ��� ���ڷ� ��ü�� �����͵� ���� �� �� �ִ�.
//�����ͷ� �����ϸ� �ּҰ� ���޵ǹǷ� call by reference�̴�.
//�� ���� ���� ������ �� �ִ�.
//�ٸ� *�����ڸ� ����Ͽ��� �ϹǷ� ���� ���ŷӴ�.
void swapObject2(Car* c1, Car* c2)
{
	Car temp;
	temp = *c1;
	*c1 = *c2;
	*c2 = temp;

	cout << "swapObject2 �ȿ��� ȣ��" << endl;
	cout << "c1 : ";
	(*c1).print();
	cout << "c2 : ";
	(*c2).print();
}

//�Լ��� ���ڷ� ��ü�� �����ڸ� ���� �� �� �ִ�.
//�����ڷ� �����ϸ� call by reference�̹Ƿ� ���� ������ �� �ִ�.
//������ ������ �������� �ʰ�, �ȿ��� *�����ڵ� ���� �����Ƿ� C++������ ���� ���� ���̴� ����̴�.
void swapObject3(Car& c1, Car& c2)
{
	Car temp;
	temp = c1;
	c1 = c2;
	c2 = temp;

	cout << "swapObject3 �ȿ��� ȣ��" << endl;
	cout << "c1 : ";
	c1.print();
	cout << "c2 : ";
	c2.print();
}

//�����ڿ� ���۷����� ���� �� ���� �ִ�.
void swapObject4(Car* c1, Car& c2)
{
	Car temp;
	temp = *c1;
	*c1 = c2;
	c2 = temp;

	cout << "swapObject4 �ȿ��� ȣ��" << endl;
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
