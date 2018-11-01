#include "matrix.h"



matrix::matrix()
{
	row = 0;
	column = 0;
}

matrix::matrix(int r, int c)
{
	row = r;
	column = c;

	number = new int*[row];
	for (int iCnt = 0; iCnt < row; iCnt++) {
		number[iCnt] = new int[column];
	}

	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			number[iCnt][kCnt] = 0;
		}
	}

}


matrix::~matrix()
{
	for (int iCnt = 0; iCnt < row; iCnt++) {
		 delete[] number[iCnt];
	}
}


void matrix::setMat()
{
	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			printf("%d행%d열의 숫자를 입력하세요 : ",iCnt, kCnt);
			cin >> number[iCnt][kCnt];
		}
	}
}

void matrix::showMat()
{
	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			printf("%3d", number[iCnt][kCnt]);
		}
		cout << endl;
	}
}

//복사 생성자
matrix::matrix(const matrix &obj)
{
	row = obj.row;
	column = obj.column;

	number = new int*[row];
	for (int iCnt = 0; iCnt < row; iCnt++) {
		number[iCnt] = new int[column];
	}

	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			number[iCnt][kCnt] = obj.number[iCnt][kCnt];
		}
	}
}



//비교 연산자
bool matrix::operator== (const matrix& m2) const
{
	if (row != m2.row || column != m2.column) { return false; }

	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			if (number[iCnt][kCnt] != m2.number[iCnt][kCnt]) {
				return false;
			}
		}
	}

	return true;
}

bool matrix::operator!= (const matrix& m2) const
{
	return !(*this == m2);
}

//사칙연산
matrix matrix::operator+ (const matrix& m2)
{
	if (row == m2.row && column == m2.column) {
		matrix mr(row, column);

		for (int iCnt = 0; iCnt < row; iCnt++) {
			for (int kCnt = 0; kCnt < column; kCnt++) {
				mr.number[iCnt][kCnt] =	number[iCnt][kCnt] + m2.number[iCnt][kCnt];
			}
		}
		return mr;
	}
	else
	{
		cout << "크기가 맞지 않습니다." << endl;
		return *this;
	}
}

matrix matrix::operator- (const matrix& m2)
{
	if (row == m2.row && column == m2.column) {
		matrix mr(row, column);

		for (int iCnt = 0; iCnt < row; iCnt++) {
			for (int kCnt = 0; kCnt < column; kCnt++) {
				mr.number[iCnt][kCnt] = number[iCnt][kCnt] - m2.number[iCnt][kCnt];
			}
		}
		return mr;
	}
	else
	{
		cout << "크기가 맞지 않습니다." << endl;
		return *this;
	}
}
matrix matrix::operator* (const matrix& v2)
{
	if (column == v2.row) {
		matrix mr(row, v2.column);

		for (int iCnt = 0; iCnt < row; iCnt++) {
			for (int kCnt = 0; kCnt < v2.column; kCnt++) {
				for (int jCnt = 0; jCnt < column; jCnt++) {
					mr.number[iCnt][kCnt] += number[iCnt][jCnt] * v2.number[jCnt][kCnt];
				}
			}
		}
		return mr;
	}
	else {
		cout << "크기가 맞지 않습니다." << endl;
		return *this;
	}

}
//matrix operator/ (matrix& v2)
//{ TODO : 역행렬
//}
//


//실수배
matrix matrix::operator* (int mag) const
{
	matrix mr(row, column);

	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			mr.number[iCnt][kCnt] = number[iCnt][kCnt] * mag;
		}
	}
	return mr;
}


matrix matrix::operator/ (int div) const
{
	matrix mr(row, column);

	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			mr.number[iCnt][kCnt] = number[iCnt][kCnt] / div;
		}
	}
	return mr;
}

matrix operator*(int mag, const matrix &mt)
{
	matrix mr(mt.row, mt.column);

	for (int iCnt = 0; iCnt < mt.row; iCnt++) {
		for (int kCnt = 0; kCnt < mt.column; kCnt++) {
			mr.number[iCnt][kCnt] = mt.number[iCnt][kCnt] * mag;
		}
	}
	return mr;
}
matrix operator/ (int div, const matrix &mt)
{
	matrix mr(mt.row, mt.column);

	for (int iCnt = 0; iCnt < mt.row; iCnt++) {
		for (int kCnt = 0; kCnt < mt.column; kCnt++) {
			mr.number[iCnt][kCnt] = mt.number[iCnt][kCnt] / div;
		}
	}
	return mr;
}



//대입 연산자
matrix& matrix::operator= (const matrix& v2)
{
	row = v2.row;
	column = v2.column;

	number = new int*[row];
	for (int iCnt = 0; iCnt < row; iCnt++) {
		number[iCnt] = new int[column];
	}

	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			number[iCnt][kCnt] = v2.number[iCnt][kCnt];
		}
	}

	return *this;
}

matrix& matrix::operator+= (const matrix& m2)
{
	if (row == m2.row && column == m2.column) {

		for (int iCnt = 0; iCnt < row; iCnt++) {
			for (int kCnt = 0; kCnt < column; kCnt++) {
				number[iCnt][kCnt] = number[iCnt][kCnt] + m2.number[iCnt][kCnt];
			}
		}
		return *this;
	}
	else
	{
		cout << "크기가 맞지 않습니다." << endl;
		return *this;
	}
}
matrix& matrix::operator-= (const matrix& m2)
{
	if (row == m2.row && column == m2.column) {

		for (int iCnt = 0; iCnt < row; iCnt++) {
			for (int kCnt = 0; kCnt < column; kCnt++) {
				number[iCnt][kCnt] = number[iCnt][kCnt] - m2.number[iCnt][kCnt];
			}
		}
		return *this;
	}
	else
	{
		cout << "크기가 맞지 않습니다." << endl;
		return *this;
	}
}

matrix& matrix::operator*= (int mag)
{
	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			number[iCnt][kCnt] = number[iCnt][kCnt] * mag;
		}
	}
	return *this;
}

matrix& matrix::operator/= (int div)
{
	for (int iCnt = 0; iCnt < row; iCnt++) {
		for (int kCnt = 0; kCnt < column; kCnt++) {
			number[iCnt][kCnt] = number[iCnt][kCnt] / div;
		}
	}
	return *this;
}

int& matrix::operator[](int index)
{
	if (index / 10 > row || index % 10 > column) {
		return number[0][0];
	}
	return number[index / 10][index % 10];
}