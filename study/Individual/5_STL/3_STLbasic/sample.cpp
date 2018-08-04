#pragma region //include 구문

//include 구문
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

//1. STL은 프로그램에 필요한 자료구조와 알고리즘을 템플릿으로 제공하는 라이브러리이다.
//2. STL은 자료구조와 알고리즘을 반복자라는 구성요소를 통해 연결한다.
//
//3. STL의 구성요소들
// a. 컨테이너(Container)         : 객체를 저장하는 객체. 컬렉션 혹은 자료구조라고도 한다.
// b. 반복자(Iterator)            : 컨테이너의 원소를 가리키고, 가리키는 원소에 접근하여 다음 원소를 가리키게 하는 포인터와 비슷한 것.
// c. 알고리즘(Algorithm)         : 정렬, 삭제, 검색, 연산 등을 해결하는 일반화된 방법을 제공하는 함수 템플릿.
// d. 함수 객체(Function Object)  : 함수처럼 동작하는 객체. 컨테이너와 알고리즘 등에 클라이언트의 정책을 반영하게 한다.
// e. 어댑터(Adaptor)             : 구성 요소의 인터페이스를 변경해 새로운 인터페이스를 갖는 구성 요소로 변경한다. (새로운 구성 요소처럼 보임)
// f. 할당기(Allocator)           : 컨테이너의 메모리 할당 정책을 캡슐화한 클래스 객체. 모든 컨테이너는 자신만의 기본 할당기를 갖고 있다. 
//
//4. STL의 세 가지 특징 : 효율성, 일반화 프로그램(재사용성), 확장성


//A. 컨테이너 :
// 같은 타입을 저장, 관리할 목적으로 만들어진 클래스.
// 각각의 컨테이너들은 성능이나 메모리 사용, 지원 인터페이스 등에 큰 차이를 보이며 서로 다른 특징을 갖는다.
//
//A-1. 컨테이너의 종류
// a. 표준 시퀀스 컨테이너(standard sequence container)   : 삽입된 순서에 따라 원소의 위치가 정해지는 컨테이너                         (선형적   :: vector, deque, list)
// b. 표준 연관 컨테이너(standard associative container)  : 삽입된 순서와 별도로 특정 정렬 기준에 의해 원소가 자동 정렬되는 컨테이너.  (비선형적 :: set, multiset, map, multimap)
//
// c. 배열 기반 컨테이너(array-based container)  : 여러개의 데이터를 하나의 메모리 단위에 저장함. (vector, deque)
// d. 노드 기반 컨테이너(node-based container)   : 하나의 데이터를 하나의 메모리 단위에 저장함.   (list, set, multiset, map, multimap)

//A-a. 근사 컨테이너(almost container) : 컨테이너와 비슷하지만 표준 컨테이너의 요구사항을 지키지 못하는 것. (내장 배열, valarray, string 등)

#ifdef container_ex

int main()
{
	//정수를 저장하는 벡터 컨테이너 생성
	vector<int> iv;

	for (int i = 0; i < 5; i++) {
		iv.push_back(i+1);
	}

	for (int i = 0; i < iv.size(); i++) {
		cout << iv[i] << ' ';
	}
}

#endif


//B. 반복자 : 
// 컨테이너에 저장된 원소를 순회하고 접근화는 일반화된 방법을 제공하는 것. 
// 컨테이너와 알고리즘이 하나로 동작하게 묶어주는 인터페이스의 역할을 수행.           
// 알고리즘이 특정 컨테이너에 종속적이지 않고 독립적이면서도 언제든지 컨테이너와 결합하여 동작할 수 있게 해줌.
//
// B-1. 반복자의 특징
//  a. 반복자는 컨테이너 내부의 원소를 가리키고 접근할 수 있어야 한다. (* 연산자 오버로딩)
//  b. 반복자는 다음 원소로 이동하고 컨테이너의 모든 원소를 순회할 수 있어야 한다. (++, !=, == 연산자 오버로딩)
//
//   순차열(sequence) : 컨테이너 원소(객체)의 집합
//   반복자는 순차열의 한 원소를 가리키게 된다.
//   STL의 모든 컨테이너는 자신만의 반복자를 제공하며,
//   bigin() 메소드는 순차열의 시작을 가리키는 반복자를 반환하고,
//   end() 메소드는 순차열의 끝을 가리키는 반복자를 반환한다.
//
//   이때, 순차열의 시작 원소는 데이터가 저장된 실제 원소지만, 순차열의 끝 원소는 데이터가 저장되지 않은 가상의 원소이다.
//   begin에서 end까지를 구간이라 하며, 수학적으로 반개구간(harf-open range)이므로 [begin,end)와 같이 표시한다.
//   구간 [begin,end)뿐만 아니라, 구간 [begin,iter)와 [iter, end)도 모두 순차열이다.
//   순차열 [p,q)에서 p와 q가 같으면 (순차열의 시작과 끝이 같으면) 이 구간의 원소는 없다.

#ifdef Iterator_ex

int main()
{
	//정수를 저장하는 벡터 컨테이너 생성
	vector<int> iv;

	for (int i = 0; i < 5; i++) {
		iv.push_back(i+1);
	}

	vector<int>::iterator iter; // 반복자 생성
	//모든 컨테이너의 반복자 클래스는 내포 클래스나 typedef 타입.

	for (iter = iv.begin(); iter != iv.end(); iter++) {
		cout << *iter << ' ';  //반복자가 가리키는 원소를 역참조
	}

}

#endif

//  c. 반복자의 종류
//   1) 입력 반복자(input iterator) : 현 위치의 원소를 한 번만 읽을 수 있는 반복자                            (istream)
//   2) 출력 반복자(output iterator) : 현 위치의 원소를 한 번만 쓸 수 있는 반복자                             (ostream)
//   3) 순방향 반복자(forward iterator) : 입출력 반복자 기능에 순방향으로 이동(++)이 추가된 반복자
//   4) 양방향 반복자(bidirectional iterator) : 순방향 반복자 기능에 역방향으로 이동(--)이 추가된 반복자      (list, set, multiset, map, multimap)
//   5) 임의 접근 반복자(random access iterator) : 양방향 반복자 기능에 +,-,+=, -=, [] 연산이 추가된 반복자.  (vector, deque)


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

//C. 알고리즘 :
// 알고리즘은 순차열의 원소를 조사, 변경, 관리, 처리할 목적으로 제공됨.
// 알고리즘은 한 쌍의 반복자([begin, end))를 필요로 함.
// 대부분의 알고리즘은 순방향 반복자를 요구하지만, 몇몇 알고리즘은 임의 접근 반복자를 요구함.
//
//C-1. 알고리즘의 범주
// a. 원소를 수정하지 않는 알고리즘(nonmodifying algorithms)
// b. 원소를 수정하는 알고리즘(modifying algorithms)
// c. 제거 알고리즘(removing algorithms)
// d. 변경 알고리즘(mutating algorithms)
// e. 정렬된 범위 알고리즘(sorted range algorithms)
// f. 수치 알고리즘(numeric algorithms)

//대부분의 STL의 알고리즘은 특정 컨테이너나 원소 타입에 종속적이지 않다. (일반적이다.)
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
		cout << "찾는 수가 없음" << endl;
	}
	else {
		cout << *iter << endl;
	}
	

	iter = find(iv.begin(), iv.end(), 10);
	if (iter == iv.end()) {
		cout << "찾는 수가 없음" << endl;
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
		cout << "찾는 문자가 없음" << endl;
	}
	else {
		cout << *iter_2 << endl;
	}


	iter_2 = find(dq.begin(), dq.end(), 'g');
	if (iter_2 == dq.end()) {
		cout << "찾는 문자가 없음" << endl;
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
		cout << "찾는 수가 없음" << endl;
	}
	else {
		cout << *iter_3 << endl;
	}


	iter_3 = find(li.begin(), li.end(), 15);
	if (iter_3 == li.end()) {
		cout << "찾는 수가 없음" << endl;
	}
	else {
		cout << *iter_3 << endl;
	}
}

#endif

//sort 알고리즘은 임의 접근 반복자를 요구한다. 
#ifdef sort_ex

int main()
{
	//vector의 경우
	vector<int> iv;
	for (int i = 0; i < 5; i++) { iv.push_back(i + 1); }
	sort(iv.begin(), iv.end()); //정렬 가능   (임의 접근 반복자)


	//deque의 경우
	deque<char> dq;
	for (int i = 'a'; i < 'f'; i++) { dq.push_back(i); }
	sort(dq.begin(), dq.end()); //정렬 가능   (임의 접근 반복자)
	

	//list의 경우
	list<short> li;
	for (int i = 11; i < 15; i++) { li.push_back(i); }
	//sort(li.begin(), li.end()); //컴파일 에러 (양방향 반복자)
}

#endif

//STL에서 함수 객체는 클라이언트가 정의한 동작을 다른 구성 요소에 반영하려 할 때 사용된다.
//많은 STL 알고리즘이 함수 객체, 함수, 함수 포인터 등을 인자로 받을 수 있다.
#ifdef sort_add_functor

int main()
{
	//vector의 경우
	vector<int> iv;
	iv.push_back(4);
	iv.push_back(2);
	iv.push_back(1);
	iv.push_back(5);
	iv.push_back(3);

	vector<int>::iterator iter;

	//sort(iv.begin(), iv.end());와 sort(iv.begin(), iv.end(), less<int>());의 결과는 같다.
	sort(iv.begin(), iv.end(), less<int>()); //오름차순 정렬 	 
	for (iter = iv.begin(); iter != iv.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	sort(iv.begin(), iv.end(), greater<int>()); //오름차순 정렬
	for (iter = iv.begin(); iter != iv.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

}

#endif

//D. 어댑터 :
// 구성 요소의 인터페이스를 변경.
//
//D-1. 어댑터의 종류
// a. 컨테이너 어댑터(container adaptor)  : stack, queue, priority_queue
// b. 반복자 어댑터(iterator adaptor)     : reverse_iterator, back_insert_iterator, front_insert_iterator, insert_iterator
// d. 함수 어댑터(function adaptor)       : binder(바인더), negator(부정자), adaptor for pointers to functions(함수 포인터 어댑터)
//
//stack 컨테이너 어댑터를 이용한 정수 입출력 예제
//모든 시퀀스 컨테이너는 empty, size, push_back, pop_back, back 인터페이스(메소드)를 가지므로 stack의 컨테이너로 사용될 수 있다.
#ifdef container_adaptor

int main()
{
	//stack<int> st  : 디폴트 컨테이너 deque를 사용해 stack 컨테이너 객체 st를 생성.
	stack<int> st;

	for (int i = 0; i < 3; i++) {
		st.push(i);
	}

	for (int i = 0; i < 5; i++) {
		if (st.empty()) {
			cout << "stack에 데이터 없음" << endl;
		}
		else {
			cout << st.top() << endl; st.pop();
		}
	}



	//stack<int, vector<int>> vst : vector 컨테이너를 사용해 stack 컨테이너 객체 st를 생성.
	stack<int, vector<int>> vst; 

	for (int i = 0; i < 3; i++) {
		vst.push(i);
	}

	for (int i = 0; i < 5; i++) {
		if (vst.empty()) {
			cout << "stack에 데이터 없음" << endl;
		}
		else {
			cout << vst.top() << endl; vst.pop();
		}
	}
}

//st.push(x)     : stack에 데이터 x를 입력
//st.top()       : stack의 top에 있는 데이터를 반환
//st.pop()       : stack의 top에 있는 데이터를 삭제
//st.empty()     : stack이 비어있는지를 판단

#endif

//역방향 반복자 예제. (반복자 어댑터 예제)
//컨테이너가 가리키는 범위는 반개구간이므로 순방향 반복자로 역방향 순회를 하는건 불편하다.
//그러므로 역방향 순회가 필요할 땐 역방향 반복자를 쓰는게 좋다.
//각각의 컨테이너는 순방향 반복자와 함께 역방향 반복자도 같이 갖고 있다.
//
//역방향 반복자가 있으므로 ++ 연산자로 정방향과 역방향 순회가 모두 가능하므로,
//그러므로 STL의 알고리즘이 ++ 연산자만으로 구현되어있어도 문제가 없다.
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

	//iterator를 reverse_iterator로 변환 (순방향 반복자를 역방향 반복자로 변환)
	reverse_iterator<vector<int>::iterator> riter(v.end());
	reverse_iterator<vector<int>::iterator> end_riter(v.begin());

	for (; riter != end_riter; riter++) {
		cout << *riter << " ";
	}
	cout << endl;

	//reverse_iterator를 선언하는 다른 방법 (원래 컨테이너 안에 있는 역방향 반복자를 사용)
	vector<int>::reverse_iterator riter_b(v.rbegin()); // riter_b = v.rbegin() 이라 써도 같다.
	
	for (; riter_b != v.rend(); riter_b++) {
		cout << *riter_b << " ";
	}
	cout << endl;

	//순방향 반복자로 역방향 순회를 한 경우
	vector<int>::iterator reverse;

	for (reverse = v.end() - 1;; reverse--) {
		cout << *reverse << " ";
		if (reverse == v.begin()) { break; }
	}
	cout << endl;

	//정방향 반복자와 역방향 반복자는 서로 가리키는 값이 다르다.
	vector<int>::iterator forward = v.begin() + 3; //정방향 반복자
	vector<int>::reverse_iterator backward(forward); //를 역방향 반복자로 변환

	cout << "정방향 반복자의 값 : " << *forward << endl;
	cout << "역방향 반복자의 값 : " << *backward << endl;
	cout << endl;
}

//v.begin()  : 컨테이너의 첫 원소를 가리키는 반복자를 반환
//v.end()    : 컨테이너의 마지막 원소 다음 위치를 가리키는 반복자를 반환
//v.rbegin() : 컨테이너의 마지막 원소를 가리키는 역방향 반복자를 반환
//v.rend()   : 컨테이너의 첫 원소의 이전 위치를 가리키는 역방향 반복자를 반환

#endif

//함수 어댑터 예제
//not2() : 2개의 인자를 받아 bool값을 반환하는 함수 객체의 반환값을 반대로 바꿔주는 함수 어댑터
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

//E. 할당기 :
// 컨테이너의 메모리 할당 정보와 정책(메모리 할당 모델)을 캡슐화한 STL 구성 요소.
// 할당기는 템플릿 클래스이며 모든 컨테이너는 기본 할당기를 사용한다.
//
// C++에서 동적 메모리 할당 연산자를 오버로딩해서 쓸 수 있듯이 STL의 할당기도 직접 정의해서 사용할 수 있다. 
// 사용자 정의 할당기는 사용자가 직접 메모리 할당 방식을 제어할 필요가 있을때 사용한다.
// 다중 스레드에 최적화되고 안전한 사용자 메모리 할당 모델이 필요하거나
// 사용자가 컨테이너에 맞는 메모리 할당 모델을 설계하거나 
// 특정 구현 환경(implementation)에서 최적화된 메모리 할당 모델을 구축할 때 사용한다.
// 대부분의 프로그램에서는 기본 할당기로 충분하므로 사용자 정의 할당기에 대한 내용은 다른 책을 참고할 것.
//
// 모든 컨테이너는 템플릿 메개변수에 할당기를 인자로 받는다. 
// 기본 할당기는 allocator<T>이며 컨테이너는 템플릿 매개변수에 디폴트 매개변수 값으로 기본 할당기를 지정한다.
// ex) vector라면 vector<typename T, typename Alloc = allocator<T>>, set이라면 set<typename T, typename Pred = less<T>, Typename Alloc = allocator<T>
//
// 할당기를 직접 지정한 예
#ifdef allocator_ex

int main()
{
	//vector<저장타입, 할당기>
	vector<int, allocator<int>> v; // = vector<int>와 같음
	v.push_back(10);
	cout << *v.begin() << endl;

	//set<저장타입, 정렬기준, 할당기>
	set<int, less<int>, allocator<int>> s; // = set<int>와 같음
	s.insert(10);
	cout << *s.begin() << endl;
}

#endif

//문제풀이_1
// 1) STL 구성 요소에서 객체들을 저장하는 객체를 컨테이너라 한다.
// 2) 컨테이너의 원소를 순회하고 참조하는 객체를 반복자라 한다.
// 3) 문제 해결을 위한 일반적인 방법을 반복자를 통해 제공하여 모든 컨테이너에 사용가능한 함수 템플릿을 알고리즘이라 한다.

//문제풀이_2
// 1) 삽입 순서에 따라 원소의 위치가 결정되는 컨테이너를 시퀀스 컨테이너라 한다.
// 2) 컨테이너에 따라서 원소가 자동 정렬되는 컨테이너를 연관 컨테이너라 한다.

//문제풀이_3
// 1) 배열 기반 컨테이너인 vector와 deque는 임의 접근 반복자를 제공하며, 
//    그외 모든 STL 컨테이너는 양방향 반복자를 제공한다.
// 2) 순차열(시퀀스)은 원소의 순서 있는 집합을 의미하며, 이 순차열은 반복자 쌍(구간)으로 표현한다.

//문제풀이_4
//  A(begin) -> B -> C(iter) -> D -> E(end) 일 때, 
//  순차열 [begin, end)의 원소 : A,B,C,D
//  순차열 [begin, iter)의 원소 : A,B
//  순차열 [iter, end)의 원소 : C,D

//문제풀이_5
//  양방향 반복자가 지원하는 연산자 : *(읽고 쓰기), ++(순방향이동), --(역방향 이동), = (대입 연산), ==, !=, >, < (비교 연산) 
//  임의 접근 반복자에서는 지원하는데 양방향 반복자에서는 지원하지 않는 연산자 : [](인덱스 연산), +, - (임의 위치 이동), +=, -= (임의 위치 이동 후 대입) 

//문제풀이_6
//  1) STL 컨테이너는 자신이 지원하는 반복자를 반환하기 위한 메소드로 begin()과 end()를 제공한다.
//     begin() : 시작 원소를 가리키는 반복자를 반환, end() : 끝 위치를 가리키는 반복자를 반환
//  2) 반복자가 가리키는 원소를 참조할 때는 * 연산자를 사용한다.

//문제풀이_7
//  1) 어댑터는 구성 요소의 인터페이스를 변경한다.
//  2) stack, queue, priority_queue는 컨테이너 어댑터라 하며, 
//     reverse_iterator, insert_iterator 등을 반복자 어댑터라 한다.
//  3) 함수 어댑터에는 바인더(binder), 부정자(negator)등이 있다.