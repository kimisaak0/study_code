#include "solution.h"

int main() {

	int max = 0;
	while (true) {
		std::cout << "�� �ο��� ������� �Է��ϼ���.\n";
		std::cin >> max;
		if (max <= 0) {
			getc(stdin);
			std::cout << "�̹� �� �׾����ϱ�?\n";
			std::cin >> max;
		}
		else {
			break;
		}
	}

	CircularList solution(max);

	int live = 0;
	while (true) {
		std::cout << "��Ƴ��� �ο��� ������� �Է��ϼ���.\n";
		std::cin >> live;
		if (live <= 0) {
			getc(stdin);
			std::cout << "�ƹ��� �׷��� 1���̻� ����ݽô�. \n";
			std::cin >> live;
		}
		else if (live > max) {
			getc(stdin);
			std::cout << "�׸�ŭ�� �ο��� �����ϴ�. \n";
			std::cin >> live;
		}
		else {
			break;
		}
	}


	int die = 0;
	std::cout << "�� �� ���� ������ ���ϼ���.\n";
	std::cin >> die;

	solution.LastN(live, die);

}