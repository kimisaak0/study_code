#pragma region //include ����

//include ����
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

using std::reverse_iterator;
using std::allocator;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <deque>
using std::deque;

#include <list>
using std::list;

#include <set>
using std::set;

#include <stack>
using std::stack;

#include <algorithm>
using std::find;
using std::sort;

#include <functional>
using std::less;
using std::greater;
using std::not2;


#pragma endregion

//container_ex, Iterator_ex, RAI_vector, RAI_deque, find_ex, solt_ex, sort_add_functor, container_adaptor, iterator_adaptor, function_adaptor, allocator_ex
#define iterator_adaptor

//1. STL�� ���α׷��� �ʿ��� �ڷᱸ���� �˰����� ���ø����� �����ϴ� ���̺귯���̴�.
//2. STL�� �ڷᱸ���� �˰����� �ݺ��ڶ�� ������Ҹ� ���� �����Ѵ�.
//
//3. STL�� ������ҵ�
// a. �����̳�(Container)         : ��ü�� �����ϴ� ��ü. �÷��� Ȥ�� �ڷᱸ����� �Ѵ�.
// b. �ݺ���(Iterator)            : �����̳��� ���Ҹ� ����Ű��, ����Ű�� ���ҿ� �����Ͽ� ���� ���Ҹ� ����Ű�� �ϴ� �����Ϳ� ����� ��.
// c. �˰���(Algorithm)         : ����, ����, �˻�, ���� ���� �ذ��ϴ� �Ϲ�ȭ�� ����� �����ϴ� �Լ� ���ø�.
// d. �Լ� ��ü(Function Object)  : �Լ�ó�� �����ϴ� ��ü. �����̳ʿ� �˰��� � Ŭ���̾�Ʈ�� ��å�� �ݿ��ϰ� �Ѵ�.
// e. �����(Adaptor)             : ���� ����� �������̽��� ������ ���ο� �������̽��� ���� ���� ��ҷ� �����Ѵ�. (���ο� ���� ���ó�� ����)
// f. �Ҵ��(Allocator)           : �����̳��� �޸� �Ҵ� ��å�� ĸ��ȭ�� Ŭ���� ��ü. ��� �����̳ʴ� �ڽŸ��� �⺻ �Ҵ�⸦ ���� �ִ�. 
//
//4. STL�� �� ���� Ư¡ : ȿ����, �Ϲ�ȭ ���α׷�(���뼺), Ȯ�强


//A. �����̳� :
// ���� Ÿ���� ����, ������ �������� ������� Ŭ����.
// ������ �����̳ʵ��� �����̳� �޸� ���, ���� �������̽� � ū ���̸� ���̸� ���� �ٸ� Ư¡�� ���´�.
//
//A-1. �����̳��� ����
// a. ǥ�� ������ �����̳�(standard sequence container)   : ���Ե� ������ ���� ������ ��ġ�� �������� �����̳�                         (������   :: vector, deque, list)
// b. ǥ�� ���� �����̳�(standard associative container)  : ���Ե� ������ ������ Ư�� ���� ���ؿ� ���� ���Ұ� �ڵ� ���ĵǴ� �����̳�.  (������ :: set, multiset, map, multimap)
//
// c. �迭 ��� �����̳�(array-based container)  : �������� �����͸� �ϳ��� �޸� ������ ������. (vector, deque)
// d. ��� ��� �����̳�(node-based container)   : �ϳ��� �����͸� �ϳ��� �޸� ������ ������.   (list, set, multiset, map, multimap)

//A-a. �ٻ� �����̳�(almost container) : �����̳ʿ� ��������� ǥ�� �����̳��� �䱸������ ��Ű�� ���ϴ� ��. (���� �迭, valarray, string ��)

#ifdef container_ex

int main()
{
	//������ �����ϴ� ���� �����̳� ����
	vector<int> iv;

	for (int i = 0; i < 5; i++) {
		iv.push_back(i+1);
	}

	for (int i = 0; i < iv.size(); i++) {
		cout << iv[i] << ' ';
	}
}

#endif


//B. �ݺ��� : 
// �����̳ʿ� ����� ���Ҹ� ��ȸ�ϰ� ����ȭ�� �Ϲ�ȭ�� ����� �����ϴ� ��. 
// �����̳ʿ� �˰����� �ϳ��� �����ϰ� �����ִ� �������̽��� ������ ����.           
// �˰����� Ư�� �����̳ʿ� ���������� �ʰ� �������̸鼭�� �������� �����̳ʿ� �����Ͽ� ������ �� �ְ� ����.
//
// B-1. �ݺ����� Ư¡
//  a. �ݺ��ڴ� �����̳� ������ ���Ҹ� ����Ű�� ������ �� �־�� �Ѵ�. (* ������ �����ε�)
//  b. �ݺ��ڴ� ���� ���ҷ� �̵��ϰ� �����̳��� ��� ���Ҹ� ��ȸ�� �� �־�� �Ѵ�. (++, !=, == ������ �����ε�)
//
//   ������(sequence) : �����̳� ����(��ü)�� ����
//   �ݺ��ڴ� �������� �� ���Ҹ� ����Ű�� �ȴ�.
//   STL�� ��� �����̳ʴ� �ڽŸ��� �ݺ��ڸ� �����ϸ�,
//   bigin() �޼ҵ�� �������� ������ ����Ű�� �ݺ��ڸ� ��ȯ�ϰ�,
//   end() �޼ҵ�� �������� ���� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
//
//   �̶�, �������� ���� ���Ҵ� �����Ͱ� ����� ���� ��������, �������� �� ���Ҵ� �����Ͱ� ������� ���� ������ �����̴�.
//   begin���� end������ �����̶� �ϸ�, ���������� �ݰ�����(harf-open range)�̹Ƿ� [begin,end)�� ���� ǥ���Ѵ�.
//   ���� [begin,end)�Ӹ� �ƴ϶�, ���� [begin,iter)�� [iter, end)�� ��� �������̴�.
//   ������ [p,q)���� p�� q�� ������ (�������� ���۰� ���� ������) �� ������ ���Ҵ� ����.

#ifdef Iterator_ex

int main()
{
	//������ �����ϴ� ���� �����̳� ����
	vector<int> iv;

	for (int i = 0; i < 5; i++) {
		iv.push_back(i+1);
	}

	vector<int>::iterator iter; // �ݺ��� ����
	//��� �����̳��� �ݺ��� Ŭ������ ���� Ŭ������ typedef Ÿ��.

	for (iter = iv.begin(); iter != iv.end(); iter++) {
		cout << *iter << ' ';  //�ݺ��ڰ� ����Ű�� ���Ҹ� ������
	}

}

#endif

//  c. �ݺ����� ����
//   1) �Է� �ݺ���(input iterator) : �� ��ġ�� ���Ҹ� �� ���� ���� �� �ִ� �ݺ���                            (istream)
//   2) ��� �ݺ���(output iterator) : �� ��ġ�� ���Ҹ� �� ���� �� �� �ִ� �ݺ���                             (ostream)
//   3) ������ �ݺ���(forward iterator) : ����� �ݺ��� ��ɿ� ���������� �̵�(++)�� �߰��� �ݺ���
//   4) ����� �ݺ���(bidirectional iterator) : ������ �ݺ��� ��ɿ� ���������� �̵�(--)�� �߰��� �ݺ���      (list, set, multiset, map, multimap)
//   5) ���� ���� �ݺ���(random access iterator) : ����� �ݺ��� ��ɿ� +,-,+=, -=, [] ������ �߰��� �ݺ���.  (vector, deque)


#ifdef RAI_vector

int main()
{
	vector<int> iv;

	for (int i = 0; i < 5; i++) {
		iv.push_back(i+1);
	}

	vector<int>::iterator iter = iv.begin(); 
	
	for (int i = 0; i < iv.size(); i++) {
		cout << iter[i] << ' ';
	}
	cout << endl;

	iter += 2; 
	cout << *iter << endl;

	vector<int>::iterator iter2 = iter + 2;
	cout << *iter2 << endl;
}

#endif

#ifdef RAI_deque

int main()
{
	deque<int> dq;

	for (int i = 0; i < 5; i++) {
		dq.push_back(i + 1);
	}

	deque<int>::iterator iter = dq.begin();

	for (int i = 0; i < dq.size(); i++) {
		cout << iter[i] << ' ';
	}
	cout << endl;

	iter += 2;
	cout << *iter << endl;

	deque<int>::iterator iter2 = iter + 2;
	cout << *iter2 << endl;
}

#endif

//C. �˰��� :
// �˰����� �������� ���Ҹ� ����, ����, ����, ó���� �������� ������.
// �˰����� �� ���� �ݺ���([begin, end))�� �ʿ�� ��.
// ��κ��� �˰����� ������ �ݺ��ڸ� �䱸������, ��� �˰����� ���� ���� �ݺ��ڸ� �䱸��.
//
//C-1. �˰����� ����
// a. ���Ҹ� �������� �ʴ� �˰���(nonmodifying algorithms)
// b. ���Ҹ� �����ϴ� �˰���(modifying algorithms)
// c. ���� �˰���(removing algorithms)
// d. ���� �˰���(mutating algorithms)
// e. ���ĵ� ���� �˰���(sorted range algorithms)
// f. ��ġ �˰���(numeric algorithms)

//��κ��� STL�� �˰����� Ư�� �����̳ʳ� ���� Ÿ�Կ� ���������� �ʴ�. (�Ϲ����̴�.)
#ifdef find_ex

int main()
{
	vector<int> iv;

	for (int i = 0; i < 5; i++) {
		iv.push_back(i + 1);
	}

	vector<int>::iterator iter = iv.begin();

	iter = find(iv.begin(), iv.end(), 2); 
	if (iter == iv.end()) {
		cout << "ã�� ���� ����" << endl;
	}
	else {
		cout << *iter << endl;
	}
	

	iter = find(iv.begin(), iv.end(), 10);
	if (iter == iv.end()) {
		cout << "ã�� ���� ����" << endl;
	}
	else {
		cout << *iter << endl;
	}

	deque<char> dq;

	for (int i = 'a'; i < 'f'; i++) {
		dq.push_back(i);
	}

	deque<char>::iterator iter_2 = dq.begin();

	iter_2 = find(dq.begin(), dq.end(), 'a');
	if (iter_2 == dq.end()) {
		cout << "ã�� ���ڰ� ����" << endl;
	}
	else {
		cout << *iter_2 << endl;
	}


	iter_2 = find(dq.begin(), dq.end(), 'g');
	if (iter_2 == dq.end()) {
		cout << "ã�� ���ڰ� ����" << endl;
	}
	else {
		cout << *iter_2 << endl;
	}


	list<short> li;

	for (int i = 11; i < 15; i++) {
		li.push_back(i);
	}

	list<short>::iterator iter_3 = li.begin();

	iter_3 = find(li.begin(), li.end(), 12);
	if (iter_3 == li.end()) {
		cout << "ã�� ���� ����" << endl;
	}
	else {
		cout << *iter_3 << endl;
	}


	iter_3 = find(li.begin(), li.end(), 15);
	if (iter_3 == li.end()) {
		cout << "ã�� ���� ����" << endl;
	}
	else {
		cout << *iter_3 << endl;
	}
}

#endif

//sort �˰����� ���� ���� �ݺ��ڸ� �䱸�Ѵ�. 
#ifdef sort_ex

int main()
{
	//vector�� ���
	vector<int> iv;
	for (int i = 0; i < 5; i++) { iv.push_back(i + 1); }
	sort(iv.begin(), iv.end()); //���� ����   (���� ���� �ݺ���)


	//deque�� ���
	deque<char> dq;
	for (int i = 'a'; i < 'f'; i++) { dq.push_back(i); }
	sort(dq.begin(), dq.end()); //���� ����   (���� ���� �ݺ���)
	

	//list�� ���
	list<short> li;
	for (int i = 11; i < 15; i++) { li.push_back(i); }
	//sort(li.begin(), li.end()); //������ ���� (����� �ݺ���)
}

#endif

//STL���� �Լ� ��ü�� Ŭ���̾�Ʈ�� ������ ������ �ٸ� ���� ��ҿ� �ݿ��Ϸ� �� �� ���ȴ�.
//���� STL �˰����� �Լ� ��ü, �Լ�, �Լ� ������ ���� ���ڷ� ���� �� �ִ�.
#ifdef sort_add_functor

int main()
{
	//vector�� ���
	vector<int> iv;
	iv.push_back(4);
	iv.push_back(2);
	iv.push_back(1);
	iv.push_back(5);
	iv.push_back(3);

	vector<int>::iterator iter;

	//sort(iv.begin(), iv.end());�� sort(iv.begin(), iv.end(), less<int>());�� ����� ����.
	sort(iv.begin(), iv.end(), less<int>()); //�������� ���� 	 
	for (iter = iv.begin(); iter != iv.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	sort(iv.begin(), iv.end(), greater<int>()); //�������� ����
	for (iter = iv.begin(); iter != iv.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

}

#endif

//D. ����� :
// ���� ����� �������̽��� ����.
//
//D-1. ������� ����
// a. �����̳� �����(container adaptor)  : stack, queue, priority_queue
// b. �ݺ��� �����(iterator adaptor)     : reverse_iterator, back_insert_iterator, front_insert_iterator, insert_iterator
// d. �Լ� �����(function adaptor)       : binder(���δ�), negator(������), adaptor for pointers to functions(�Լ� ������ �����)
//
//stack �����̳� ����͸� �̿��� ���� ����� ����
//��� ������ �����̳ʴ� empty, size, push_back, pop_back, back �������̽�(�޼ҵ�)�� �����Ƿ� stack�� �����̳ʷ� ���� �� �ִ�.
#ifdef container_adaptor

int main()
{
	//stack<int> st  : ����Ʈ �����̳� deque�� ����� stack �����̳� ��ü st�� ����.
	stack<int> st;

	for (int i = 0; i < 3; i++) {
		st.push(i);
	}

	for (int i = 0; i < 5; i++) {
		if (st.empty()) {
			cout << "stack�� ������ ����" << endl;
		}
		else {
			cout << st.top() << endl; st.pop();
		}
	}



	//stack<int, vector<int>> vst : vector �����̳ʸ� ����� stack �����̳� ��ü st�� ����.
	stack<int, vector<int>> vst; 

	for (int i = 0; i < 3; i++) {
		vst.push(i);
	}

	for (int i = 0; i < 5; i++) {
		if (vst.empty()) {
			cout << "stack�� ������ ����" << endl;
		}
		else {
			cout << vst.top() << endl; vst.pop();
		}
	}
}

//st.push(x)     : stack�� ������ x�� �Է�
//st.top()       : stack�� top�� �ִ� �����͸� ��ȯ
//st.pop()       : stack�� top�� �ִ� �����͸� ����
//st.empty()     : stack�� ����ִ����� �Ǵ�

#endif

//������ �ݺ��� ����. (�ݺ��� ����� ����)
//�����̳ʰ� ����Ű�� ������ �ݰ������̹Ƿ� ������ �ݺ��ڷ� ������ ��ȸ�� �ϴ°� �����ϴ�.
//�׷��Ƿ� ������ ��ȸ�� �ʿ��� �� ������ �ݺ��ڸ� ���°� ����.
//������ �����̳ʴ� ������ �ݺ��ڿ� �Բ� ������ �ݺ��ڵ� ���� ���� �ִ�.
//
//������ �ݺ��ڰ� �����Ƿ� ++ �����ڷ� ������� ������ ��ȸ�� ��� �����ϹǷ�,
//�׷��Ƿ� STL�� �˰����� ++ �����ڸ����� �����Ǿ��־ ������ ����.
#ifdef iterator_adaptor

int main()
{
	vector<int> v;

	for (int i = 0; i < 5; i++) {
		v.push_back(i);
	}

	vector<int>::iterator iter = v.begin();
	for (; iter != v.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	//iterator�� reverse_iterator�� ��ȯ (������ �ݺ��ڸ� ������ �ݺ��ڷ� ��ȯ)
	reverse_iterator<vector<int>::iterator> riter(v.end());
	reverse_iterator<vector<int>::iterator> end_riter(v.begin());

	for (; riter != end_riter; riter++) {
		cout << *riter << " ";
	}
	cout << endl;

	//reverse_iterator�� �����ϴ� �ٸ� ��� (���� �����̳� �ȿ� �ִ� ������ �ݺ��ڸ� ���)
	vector<int>::reverse_iterator riter_b(v.rbegin()); // riter_b = v.rbegin() �̶� �ᵵ ����.
	
	for (; riter_b != v.rend(); riter_b++) {
		cout << *riter_b << " ";
	}
	cout << endl;

	//������ �ݺ��ڷ� ������ ��ȸ�� �� ���
	vector<int>::iterator reverse;

	for (reverse = v.end() - 1;; reverse--) {
		cout << *reverse << " ";
		if (reverse == v.begin()) { break; }
	}
	cout << endl;

	//������ �ݺ��ڿ� ������ �ݺ��ڴ� ���� ����Ű�� ���� �ٸ���.
	vector<int>::iterator forward = v.begin() + 3; //������ �ݺ���
	vector<int>::reverse_iterator backward(forward); //�� ������ �ݺ��ڷ� ��ȯ

	cout << "������ �ݺ����� �� : " << *forward << endl;
	cout << "������ �ݺ����� �� : " << *backward << endl;
	cout << endl;
}

//v.begin()  : �����̳��� ù ���Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ
//v.end()    : �����̳��� ������ ���� ���� ��ġ�� ����Ű�� �ݺ��ڸ� ��ȯ
//v.rbegin() : �����̳��� ������ ���Ҹ� ����Ű�� ������ �ݺ��ڸ� ��ȯ
//v.rend()   : �����̳��� ù ������ ���� ��ġ�� ����Ű�� ������ �ݺ��ڸ� ��ȯ

#endif

//�Լ� ����� ����
//not2() : 2���� ���ڸ� �޾� bool���� ��ȯ�ϴ� �Լ� ��ü�� ��ȯ���� �ݴ�� �ٲ��ִ� �Լ� �����
#ifdef function_adaptor

int main()
{
	cout << "less<int>()(...)" << endl;
	cout << less<int>() (10, 20) << endl;
	cout << less<int>() (20, 20) << endl;
	cout << less<int>() (20, 10) << endl;
	cout << endl;

	cout << "not2(less<int>())(...)" << endl;
	cout << not2(less<int>())(10, 20) << endl;
	cout << not2(less<int>())(20, 20) << endl;
	cout << not2(less<int>())(20, 10) << endl;

	cout << "less<int> L" << endl << endl;;
	less<int> L;
	

	cout << "L(...)" << endl;
	cout <<L(10, 20) << endl;
	cout <<L(20, 20) << endl;
	cout <<L(20, 10) << endl;
	cout << endl;

	cout << "not2(L)(...)" << endl;
	cout << not2(L)(10, 20) << endl;
	cout << not2(L)(20, 20) << endl;
	cout << not2(L)(20, 10) << endl;

}

#endif

//E. �Ҵ�� :
// �����̳��� �޸� �Ҵ� ������ ��å(�޸� �Ҵ� ��)�� ĸ��ȭ�� STL ���� ���.
// �Ҵ��� ���ø� Ŭ�����̸� ��� �����̳ʴ� �⺻ �Ҵ�⸦ ����Ѵ�.
//
// C++���� ���� �޸� �Ҵ� �����ڸ� �����ε��ؼ� �� �� �ֵ��� STL�� �Ҵ�⵵ ���� �����ؼ� ����� �� �ִ�. 
// ����� ���� �Ҵ��� ����ڰ� ���� �޸� �Ҵ� ����� ������ �ʿ䰡 ������ ����Ѵ�.
// ���� �����忡 ����ȭ�ǰ� ������ ����� �޸� �Ҵ� ���� �ʿ��ϰų�
// ����ڰ� �����̳ʿ� �´� �޸� �Ҵ� ���� �����ϰų� 
// Ư�� ���� ȯ��(implementation)���� ����ȭ�� �޸� �Ҵ� ���� ������ �� ����Ѵ�.
// ��κ��� ���α׷������� �⺻ �Ҵ��� ����ϹǷ� ����� ���� �Ҵ�⿡ ���� ������ �ٸ� å�� ������ ��.
//
// ��� �����̳ʴ� ���ø� �ް������� �Ҵ�⸦ ���ڷ� �޴´�. 
// �⺻ �Ҵ��� allocator<T>�̸� �����̳ʴ� ���ø� �Ű������� ����Ʈ �Ű����� ������ �⺻ �Ҵ�⸦ �����Ѵ�.
// ex) vector��� vector<typename T, typename Alloc = allocator<T>>, set�̶�� set<typename T, typename Pred = less<T>, Typename Alloc = allocator<T>
//
// �Ҵ�⸦ ���� ������ ��
#ifdef allocator_ex

int main()
{
	//vector<����Ÿ��, �Ҵ��>
	vector<int, allocator<int>> v; // = vector<int>�� ����
	v.push_back(10);
	cout << *v.begin() << endl;

	//set<����Ÿ��, ���ı���, �Ҵ��>
	set<int, less<int>, allocator<int>> s; // = set<int>�� ����
	s.insert(10);
	cout << *s.begin() << endl;
}

#endif

//����Ǯ��_1
// 1) STL ���� ��ҿ��� ��ü���� �����ϴ� ��ü�� �����̳ʶ� �Ѵ�.
// 2) �����̳��� ���Ҹ� ��ȸ�ϰ� �����ϴ� ��ü�� �ݺ��ڶ� �Ѵ�.
// 3) ���� �ذ��� ���� �Ϲ����� ����� �ݺ��ڸ� ���� �����Ͽ� ��� �����̳ʿ� ��밡���� �Լ� ���ø��� �˰����̶� �Ѵ�.

//����Ǯ��_2
// 1) ���� ������ ���� ������ ��ġ�� �����Ǵ� �����̳ʸ� ������ �����̳ʶ� �Ѵ�.
// 2) �����̳ʿ� ���� ���Ұ� �ڵ� ���ĵǴ� �����̳ʸ� ���� �����̳ʶ� �Ѵ�.

//����Ǯ��_3
// 1) �迭 ��� �����̳��� vector�� deque�� ���� ���� �ݺ��ڸ� �����ϸ�, 
//    �׿� ��� STL �����̳ʴ� ����� �ݺ��ڸ� �����Ѵ�.
// 2) ������(������)�� ������ ���� �ִ� ������ �ǹ��ϸ�, �� �������� �ݺ��� ��(����)���� ǥ���Ѵ�.

//����Ǯ��_4
//  A(begin) -> B -> C(iter) -> D -> E(end) �� ��, 
//  ������ [begin, end)�� ���� : A,B,C,D
//  ������ [begin, iter)�� ���� : A,B
//  ������ [iter, end)�� ���� : C,D

//����Ǯ��_5
//  ����� �ݺ��ڰ� �����ϴ� ������ : *(�а� ����), ++(�������̵�), --(������ �̵�), = (���� ����), ==, !=, >, < (�� ����) 
//  ���� ���� �ݺ��ڿ����� �����ϴµ� ����� �ݺ��ڿ����� �������� �ʴ� ������ : [](�ε��� ����), +, - (���� ��ġ �̵�), +=, -= (���� ��ġ �̵� �� ����) 

//����Ǯ��_6
//  1) STL �����̳ʴ� �ڽ��� �����ϴ� �ݺ��ڸ� ��ȯ�ϱ� ���� �޼ҵ�� begin()�� end()�� �����Ѵ�.
//     begin() : ���� ���Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ, end() : �� ��ġ�� ����Ű�� �ݺ��ڸ� ��ȯ
//  2) �ݺ��ڰ� ����Ű�� ���Ҹ� ������ ���� * �����ڸ� ����Ѵ�.

//����Ǯ��_7
//  1) ����ʹ� ���� ����� �������̽��� �����Ѵ�.
//  2) stack, queue, priority_queue�� �����̳� ����Ͷ� �ϸ�, 
//     reverse_iterator, insert_iterator ���� �ݺ��� ����Ͷ� �Ѵ�.
//  3) �Լ� ����Ϳ��� ���δ�(binder), ������(negator)���� �ִ�.