#include "solution.h"

int main() {

	int max = 0;
	while (true) {
		std::cout << "총 인원이 몇명인지 입력하세요.\n";
		std::cin >> max;
		if (max <= 0) {
			getc(stdin);
			std::cout << "이미 다 죽었습니까?\n";
			std::cin >> max;
		}
		else {
			break;
		}
	}

	CircularList solution(max);

	int live = 0;
	while (true) {
		std::cout << "살아남은 인원이 몇명인지 입력하세요.\n";
		std::cin >> live;
		if (live <= 0) {
			getc(stdin);
			std::cout << "아무리 그래도 1명이상 살려줍시다. \n";
			std::cin >> live;
		}
		else if (live > max) {
			getc(stdin);
			std::cout << "그만큼의 인원이 없습니다. \n";
			std::cin >> live;
		}
		else {
			break;
		}
	}


	int die = 0;
	std::cout << "몇 명 마다 죽일지 정하세요.\n";
	std::cin >> die;

	solution.LastN(live, die);

}