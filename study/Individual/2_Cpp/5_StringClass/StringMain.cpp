//char형 배열로 문자열을 표현하는 것을 대신하는 string클래스

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	//string 클래스 사용
	cout << endl << "string클래스의 객체 s 선언하고 초기화" << endl;
	string s = "This is a test";	//string 객체를 생성하고 초기화
	cout << s << endl;

	//멤버 함수 호출하기
	cout << endl << "객체 s의 멤버 함수 호출하기" << endl;
	size_t size = s.size();
	cout << size << endl;

	//string클래스로 문자열 결합하기
	cout << endl << "문자열 결합하기" << endl;
	string sub = "money";
	string other = "has no value if it is not used";
	string sentence1 = sub + other;
	string sentence2 = "this" + other;

	cout << "sub : " << sub << endl;
	cout << "other : " << other << endl;
	cout << "sentence1 : " << sentence1 << endl;
	cout << "sentence2 : " << sentence1 << endl;

	//객체에 객체 대입하기
	cout << endl << "string객체에 string객체 대입하기" << endl;
	string s1 = sentence1;
	cout << "s1 : "  << s1 << endl;

	//기존의 문자열에 다른 문자열 추가하기
	cout << endl << "문자열 추가하기" << endl;
	string s2 = sub;
	string s3 = other;

	cout << "s2 : " << s2 << endl;
	cout << "s3 : " << s3 << endl;

	s2 += s3;
	cout << "s2 : " << s2 << endl;

	//문자열 비교하기
	cout << endl << "문자열 비교하기" << endl;
	cout << "s1 == s2 : " << (s1 == s2) << endl;

	if (s1 == s2) {
		cout << "동일한 문자열입니다." << endl;
	}
	else {
		cout << "동일한 문자열이 아닙니다." << endl;
	}

	cout << endl;
	cout << "s1 : " << s1 << endl;
	cout << "s2 : " << s2 << endl;
	cout << "s3 : " << s3 << endl;

	cout << endl;
	cout << "참이면 1, 거짓이면 0" << endl;
	cout << "s2 > s3 : " << (s2 > s3) << ", s2 < s3 : " << (s2 < s3) << endl;
	

	if (s2 > s3) {
		cout << "s2이 s3 앞에 있습니다." << endl;
	}
	else {
		cout << "s2이 s3 뒤에 있습니다." << endl;
	}

	//입력 받기
	cout << endl << "한줄 입력받기" << endl;
	string s4;

	//공백이 있으면 그 뒤는 입력이 안 됨
	cout << endl << "cin>>s;는 공백이 있으면 그 뒤가 저장되지 않는다." << endl;
	cin >> s4;			

	//공백을 포함한 전체줄을 string 문자열에 저장하는 방법
	cout << endl << "getline(cin,s);는 공백이 있으면 그 뒤가 저장되지 않는다." << endl;
	getline(cin, s4);	

	//줄바꿈이 나오기 전까지 한 문자씩 입력받기
	cout << endl << "한 문자씩 입력받기" << endl;
	
	char c;
	
	do {
		cin.get(c);
		s += c;
	} while (c != '\n');

	//문자 추출하기
	cout << endl << "문자열에서 문자 추출하기" << endl;

	for (int i = 0; ; i++) {
		printf("s[%d] : ", i);
		cout << s[i] << endl;
		if (s[i] == '\n') {
			break;
		}
	}
}