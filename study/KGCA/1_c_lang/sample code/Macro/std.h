#pragma once
#include <windows.h>
#include <cstdio>
#include <math.h>
////sound() => Beep()
////delay() => Sleep()

// #define DO(t) Beep((DWORD)(131*pow(1.06f,0)),(DWORD)(300*(t)));Sleep(100);
// pow(1.06f,0) == 1 / pow(1.06f,12) == 2
// Beep(������, �ð�)

//��Ÿ��   0    1    2    3    4    5    6     7     8
//  ��    016  033  065  131  262  523  1047  2093  4186

#define DO(t)	Beep((DWORD)523*pow(1.06f, 0),(DWORD)300*(t));	Sleep((DWORD)100);
#define RE(t)	Beep((DWORD)523*pow(1.06f, 2),(DWORD)300*(t));	Sleep((DWORD)100);
#define MI(t)	Beep((DWORD)523*pow(1.06f, 4),(DWORD)300*(t));	Sleep((DWORD)100);
#define FA(t)	Beep((DWORD)523*pow(1.06f, 5),(DWORD)300*(t));	Sleep((DWORD)100);
#define SO(t)	Beep((DWORD)523*pow(1.06f, 7),(DWORD)300*(t));	Sleep((DWORD)100);
#define RA(t)	Beep((DWORD)523*pow(1.06f, 9),(DWORD)300*(t));	Sleep((DWORD)100);
#define SI(t)	Beep((DWORD)523*pow(1.06f,11),(DWORD)300*(t));	Sleep((DWORD)100);
#define _DO(t)	Beep((DWORD)523*pow(1.06f,12),(DWORD)300*(t));	Sleep((DWORD)100);

//��ũ�� �ȿ� ��ũ�� �ֱ�
#define TBASIS_PI			((FLOAT)  3.141592654f)
#define DegreeToRadian( degree ) ((degree) * (TBASIS_PI / 180.0f))
#define RadianToDegree( radian ) ((radian) * (180.0f / TBASIS_PI))

//��ũ�η� �峭ġ��
#define A(t)    if(t) { 
#define EndMain    }
#define StartMain int main() {
#define X int a=1;
#define P(r)printf(r);

