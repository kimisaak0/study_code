//string Ŭ������ ��� �Լ�

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main()
{
	//.assign : ���ڿ� �Ҵ� 	
	string s1;
	cout << ".assign" << endl << endl;

	s1.assign("s1.assign");			// (���ڿ�) : �Ű������� ���� ���ڿ� �Ҵ�
	cout << s1 << endl;

	s1.assign(3, '!');				// (����, ����) : �Ű������� ���� ���ڸ� ������ŭ �Ҵ�
	cout << s1 << endl;

	s1.assign(s, 5, 2);			// (���ڿ�, ������ġ, ����) : �Ű������� ���� ���ڿ����� ������ġ(0~)���� ������ŭ�� �߶� ȣ���� ���ڿ��� �Ҵ�
	cout << s1 << endl << endl;


	//.append : ���ڿ� �߰�
	string s2;
	cout << ".append" << endl << endl;

	s2.append("s2.append");			// (���ڿ�) : ���ڿ� �ڿ� �Ű������� ���� ���ڿ��� ���Ѵ�. (������ ���� �Ҵ�)
	cout << s2 << endl;
	s1.append("+append");
	cout << s1 << endl;

	s2.append(3, '+');				// (����, ����) : ���ڿ� �ڿ� �Ű������� ���� ���ڸ� ������ŭ ���Ѵ�.
	cout << s2 << endl;

	s2.append(s1, 0, 2);				// (���ڿ�, ������ġ, ����) : �Ű������� ���� ���ڿ����� ������ġ(0~)���� ������ŭ�� �߶� ȣ���� ���ڿ��� �ڿ� �߰�
	cout << s2 << endl << endl;


	//.begin : ���ڿ��� ù��° ��ġ ���� 
	string s3;
	cout << ".begin" << endl << endl;

	//cout << *(s3.begin()) << endl;	//��Ÿ�� ����

	cout << *(s2.begin()) << endl;	//���ڿ��� ù���� ���

	*(s2.begin()) = 'A';						//���ڿ��� ù���� ����
	cout << s2 << endl;

	//ù������ ��ġ�� �̿��Ͽ� ���ڿ� ��ü ����ϱ�
	for (string::iterator it = s2.begin(); it != s2.end(); it++) {
		cout << *it;
	}
	cout << endl << endl;


	//.back : ���ڿ��� ������ ���� (��������� ȣ�� X)
	string s4;
	cout << ".back" << endl << endl;

	//cout << s4.back() << endl << endl; //��Ÿ�� ����

	cout << s2.back() << endl;	//���ڿ��� ������ ���

	s2.back() = '!';						//���ڿ��� ������ ����
	cout << s2 << endl;


	//.clear : ���ڿ� ���� ����
	cout << ".clear" << endl << endl;
	s.clear();
	s1.clear();
	s2.clear();
	cout << "s : " << s << ", s1 : " << s1 << ", s2 : " << s2 << endl << endl;

	//.compare : ���ڿ��� �� (C�� strcmp�� ����)
	s = "a1";
	s1 = "a1";
	s2 = "s2";
	s3 = "s3";

	cout << s.compare(s1) << endl;
	cout << s2.compare(s1) << endl;
	cout << s2.compare(s3) << endl << endl;
}