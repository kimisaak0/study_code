//string 클래스의 멤버 함수

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main()
{
	//.assign : 문자열 할당 	
	string s1;
	cout << ".assign" << endl << endl;

	s1.assign("s1.assign");			// (문자열) : 매개변수로 받은 문자열 할당
	cout << s1 << endl;

	s1.assign(3, '!');				// (개수, 문자) : 매개변수로 받은 문자를 갯수만큼 할당
	cout << s1 << endl;

	s1.assign(s, 5, 2);			// (문자열, 시작위치, 개수) : 매개변수로 받은 문자열에서 시작위치(0~)부터 개수만큼을 잘라서 호출한 문자열에 할당
	cout << s1 << endl << endl;


	//.append : 문자열 추가
	string s2;
	cout << ".append" << endl << endl;

	s2.append("s2.append");			// (문자열) : 문자열 뒤에 매개변수로 받은 문자열을 더한다. (없으면 새로 할당)
	cout << s2 << endl;
	s1.append("+append");
	cout << s1 << endl;

	s2.append(3, '+');				// (개수, 문자) : 문자열 뒤에 매개변수로 받은 문자를 개수만큼 더한다.
	cout << s2 << endl;

	s2.append(s1, 0, 2);				// (문자열, 시작위치, 개수) : 매개변수로 받은 문자열에서 시작위치(0~)부터 개수만큼을 잘라서 호출한 문자열의 뒤에 추가
	cout << s2 << endl << endl;


	//.begin : 문자열의 첫번째 위치 리턴 
	string s3;
	cout << ".begin" << endl << endl;

	//cout << *(s3.begin()) << endl;	//런타임 에러

	cout << *(s2.begin()) << endl;	//문자열의 첫문자 출력

	*(s2.begin()) = 'A';						//문자열의 첫문자 변경
	cout << s2 << endl;

	//첫문자의 위치를 이용하여 문자열 전체 출력하기
	for (string::iterator it = s2.begin(); it != s2.end(); it++) {
		cout << *it;
	}
	cout << endl << endl;


	//.back : 문자열의 끝문자 리턴 (비어있으면 호출 X)
	string s4;
	cout << ".back" << endl << endl;

	//cout << s4.back() << endl << endl; //런타임 에러

	cout << s2.back() << endl;	//문자열의 끝문자 출력

	s2.back() = '!';						//문자열의 끝문자 변경
	cout << s2 << endl;


	//.clear : 문자열 내용 삭제
	cout << ".clear" << endl << endl;
	s.clear();
	s1.clear();
	s2.clear();
	cout << "s : " << s << ", s1 : " << s1 << ", s2 : " << s2 << endl << endl;

	//.compare : 문자열을 비교 (C의 strcmp랑 같음)
	s = "a1";
	s1 = "a1";
	s2 = "s2";
	s3 = "s3";

	cout << s.compare(s1) << endl;
	cout << s2.compare(s1) << endl;
	cout << s2.compare(s3) << endl << endl;
}