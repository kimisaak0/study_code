//char�� �迭�� ���ڿ��� ǥ���ϴ� ���� ����ϴ� stringŬ����

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	//string Ŭ���� ���
	cout << endl << "stringŬ������ ��ü s �����ϰ� �ʱ�ȭ" << endl;
	string s = "This is a test";	//string ��ü�� �����ϰ� �ʱ�ȭ
	cout << s << endl;

	//��� �Լ� ȣ���ϱ�
	cout << endl << "��ü s�� ��� �Լ� ȣ���ϱ�" << endl;
	size_t size = s.size();
	cout << size << endl;

	//stringŬ������ ���ڿ� �����ϱ�
	cout << endl << "���ڿ� �����ϱ�" << endl;
	string sub = "money";
	string other = "has no value if it is not used";
	string sentence1 = sub + other;
	string sentence2 = "this" + other;

	cout << "sub : " << sub << endl;
	cout << "other : " << other << endl;
	cout << "sentence1 : " << sentence1 << endl;
	cout << "sentence2 : " << sentence1 << endl;

	//��ü�� ��ü �����ϱ�
	cout << endl << "string��ü�� string��ü �����ϱ�" << endl;
	string s1 = sentence1;
	cout << "s1 : "  << s1 << endl;

	//������ ���ڿ��� �ٸ� ���ڿ� �߰��ϱ�
	cout << endl << "���ڿ� �߰��ϱ�" << endl;
	string s2 = sub;
	string s3 = other;

	cout << "s2 : " << s2 << endl;
	cout << "s3 : " << s3 << endl;

	s2 += s3;
	cout << "s2 : " << s2 << endl;

	//���ڿ� ���ϱ�
	cout << endl << "���ڿ� ���ϱ�" << endl;
	cout << "s1 == s2 : " << (s1 == s2) << endl;

	if (s1 == s2) {
		cout << "������ ���ڿ��Դϴ�." << endl;
	}
	else {
		cout << "������ ���ڿ��� �ƴմϴ�." << endl;
	}

	cout << endl;
	cout << "s1 : " << s1 << endl;
	cout << "s2 : " << s2 << endl;
	cout << "s3 : " << s3 << endl;

	cout << endl;
	cout << "���̸� 1, �����̸� 0" << endl;
	cout << "s2 > s3 : " << (s2 > s3) << ", s2 < s3 : " << (s2 < s3) << endl;
	

	if (s2 > s3) {
		cout << "s2�� s3 �տ� �ֽ��ϴ�." << endl;
	}
	else {
		cout << "s2�� s3 �ڿ� �ֽ��ϴ�." << endl;
	}

	//�Է� �ޱ�
	cout << endl << "���� �Է¹ޱ�" << endl;
	string s4;

	//������ ������ �� �ڴ� �Է��� �� ��
	cout << endl << "cin>>s;�� ������ ������ �� �ڰ� ������� �ʴ´�." << endl;
	cin >> s4;			

	//������ ������ ��ü���� string ���ڿ��� �����ϴ� ���
	cout << endl << "getline(cin,s);�� ������ ������ �� �ڰ� ������� �ʴ´�." << endl;
	getline(cin, s4);	

	//�ٹٲ��� ������ ������ �� ���ھ� �Է¹ޱ�
	cout << endl << "�� ���ھ� �Է¹ޱ�" << endl;
	
	char c;
	
	do {
		cin.get(c);
		s += c;
	} while (c != '\n');

	//���� �����ϱ�
	cout << endl << "���ڿ����� ���� �����ϱ�" << endl;

	for (int i = 0; ; i++) {
		printf("s[%d] : ", i);
		cout << s[i] << endl;
		if (s[i] == '\n') {
			break;
		}
	}
}