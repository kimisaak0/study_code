#include "classes.h"

int main()
{
	class_A tA(3);
	class_A tB = 4;
	class_A tC = tA;

	class_E tD(5);
	//class_E tE=3 // Error 묵시적 변환이 발생하지 못한다.
	class_E tE(tD); //OK

	class_M tF(6);

	std::cout << "tA : "<< tA.Get() << std::endl;
	std::cout << "tB : "<< tB.Get() << std::endl;
	std::cout << "tC : "<< tC.Get() << std::endl;
				
	std::cout << "tD : "<< tD.Get() << std::endl;
	std::cout << "tE : "<< tE.Get() << std::endl;
				 
	std::cout << "tF : "<< tF.Get() << std::endl;
	std::cout << "tF : "<< tF.Get(7) << std::endl;
}